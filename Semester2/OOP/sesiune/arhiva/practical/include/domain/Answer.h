//
// Created by georgerapeanu on 11.06.2022.
//

#ifndef PRACTICAL_ANSWER_H
#define PRACTICAL_ANSWER_H

#include <string>
#include <ostream>

class Answer{
    int id;
    int question_id;
    std::string answering_user_name;
    std::string answer_text;
    int votes;
public:
    int getId() const;

    int getQuestionId() const;

    void setQuestionId(int questionId);

    const std::string &getAnsweringUserName() const;

    void setAnsweringUserName(const std::string &answeringUserName);

    const std::string &getAnswerText() const;

    void setAnswerText(const std::string &answerText);

    int getVotes() const;

    void setVotes(int votes);

public:
    Answer(int id, int questionId, const std::string &answeringUserName, const std::string &answerText, int votes);

    Answer();

    friend std::ostream &operator<<(std::ostream &os, const Answer &answer);
    friend std::istream &operator>>(std::istream &is, Answer &answer);
};

#endif //PRACTICAL_ANSWER_H
