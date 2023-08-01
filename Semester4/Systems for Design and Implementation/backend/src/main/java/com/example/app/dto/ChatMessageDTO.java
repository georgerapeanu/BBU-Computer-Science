package com.example.app.dto;

import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@ToString
@EqualsAndHashCode
public class ChatMessageDTO {
    /**
     * The nickname of the user sending the chat message.
     */
    @Getter
    @Setter
    String nickname;

    /**
     * The content of the chat message.
     */
    @Getter
    @Setter
    String message;
}
