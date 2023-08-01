package com.example.app.controller;

import com.example.app.dto.ChatMessageDTO;
import com.example.app.exceptions.AppException;
import com.example.app.model.Message;
import com.example.app.model.User;
import com.example.app.repository.MessageRepository;
import com.example.app.repository.UserRepository;
import com.example.app.util.JWTUtils;
import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.env.Environment;
import org.springframework.http.*;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;

import java.util.*;
import java.util.stream.Collectors;

/**
 * Controller class for handling chat-related operations.
 */
@RestController
@CrossOrigin(origins = "*")
public class ChatController {
    @Autowired
    MessageRepository messageRepository;
    @Autowired
    UserRepository userRepository;
    @Autowired
    private Environment env;

    /**
     * Handles the incoming chat messages.
     *
     * @param chatMessageDTO the chat message DTO
     * @return the processed chat message DTO
     */
    @MessageMapping("/chat")
    @SendTo("/topic/chat")
    public ChatMessageDTO message(
            ChatMessageDTO chatMessageDTO
    ) {
        return chatMessageDTO;
    }

    /**
     * Restores the chat messages for the current user.
     *
     * @param user the authenticated user
     * @return a list of chat message DTOs
     */
    @GetMapping("/restore-messages")
    public List<ChatMessageDTO> restoreMessages(
            @RequestAttribute("user") User user
    ) {
        if (user == null) {
            return new ArrayList<>();
        }
        return messageRepository.findAllByUserHandleOrderById(user.getHandle())
                .stream()
                .map(message -> {
                    return new ChatMessageDTO(message.getNickname(), message.getMessage());
                }).collect(Collectors.toList());
    }

    /**
     * Stores a chat message for the current user.
     *
     * @param user        the authenticated user
     * @param messageDTO  the chat message DTO to be stored
     */
    @PostMapping("/store-messages")
    public void storeMessages(
            @RequestAttribute("user") User user,
            @RequestBody ChatMessageDTO messageDTO
    ) {
        if (user == null) {
            return;
        }
        Message message = new Message();
        message.setUser(user);
        message.setMessage(messageDTO.getMessage());
        message.setNickname(messageDTO.getNickname());
        message.setUserHandle(user.getHandle());
        messageRepository.save(message);
    }

    /**
     * Retrieves a summary of recent chat messages using an AI service.
     *
     * @return a summary of recent chat messages or "Unavailable" if the service is unavailable
     */
    @GetMapping(path = "/chat-recent-summary", produces = "text/plain")
    public String getRecentSummary() {
        String ai_url = env.getRequiredProperty("ai_url");
        RestTemplate restTemplate = new RestTemplate();
        HttpHeaders httpHeaders = new HttpHeaders();
        httpHeaders.setContentType(MediaType.APPLICATION_JSON);
        List<Message> recentMessages = messageRepository.findFirst4ByOrderByIdDesc();

        String text = recentMessages.stream().map(Message::getMessage).reduce("", (x, y) -> x + "." + y);
        String question = "Summarize.";

        Map<String, String> payload = new HashMap<>();
        payload.put("text", text);
        payload.put("question", question);

        HttpEntity<Map<String, String>> requestEntity = new HttpEntity<>(payload, httpHeaders);
        ResponseEntity<String> responseEntity = restTemplate.exchange(ai_url, HttpMethod.POST, requestEntity, String.class);

        if (responseEntity.getStatusCode().is2xxSuccessful()) {
            return responseEntity.getBody();
        } else {
            return "Unavailable";
        }
    }
}
