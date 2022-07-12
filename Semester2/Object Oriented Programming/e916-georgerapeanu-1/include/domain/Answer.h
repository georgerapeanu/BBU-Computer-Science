//
// Created by georgerapeanu on 12.06.2022.
//

#ifndef E916_GEORGERAPEANU_1_ANSWER_H
#define E916_GEORGERAPEANU_1_ANSWER_H

#include <string>
#include <ostream>

class Answer{
public:
    Answer(int id, int questionId, const std::string &answeringName, const std::string &text, int numberOfVotes);

    Answer();

    int getQuestionId() const;

    void setQuestionId(int questionId);

    const std::string &getAnsweringName() const;

    void setAnsweringName(const std::string &answeringName);

    const std::string &getText() const;

    void setText(const std::string &text);

    int getId() const;

    int getNumberOfVotes() const;

    void setNumberOfVotes(int numberOfVotes);

    friend std::ostream &operator<<(std::ostream &os, const Answer &answer);

    friend std::istream &operator>>(std::istream &is, Answer &answer);

private:
    int id;
    int question_id;
    std::string answering_name;
    std::string text;
    int number_of_votes;
};

#endif //E916_GEORGERAPEANU_1_ANSWER_H
