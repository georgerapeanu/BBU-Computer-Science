//
// Created by georgerapeanu on 08.06.2022.
//

#ifndef MODEL_ISSUE_H
#define MODEL_ISSUE_H

#include <string>
#include <ostream>

class Issue{
    std::string description;
public:
    enum Status{
        OPEN,
        CLOSED
    };
private:
    Status status;
    std::string reporter;
    std::string solver;

public:
    Issue();

    Issue(const std::string &description, Status status, const std::string &reporter, const std::string &solver);

    const std::string &getId() const;

    const std::string &getDescription() const;

    void setDescription(const std::string &description);

    Status getStatus() const;

    void setStatus(Status status);

    const std::string &getReporter() const;

    void setReporter(const std::string &reporter);

    const std::string &getSolver() const;

    void setSolver(const std::string &solver);

    friend std::ostream &operator<<(std::ostream &os, const Issue &issue);

    friend std::istream &operator>>(std::istream &is, Issue &issue);

    bool operator == (const Issue &other)const;
};

#endif //MODEL_ISSUE_H
