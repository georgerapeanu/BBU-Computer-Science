//
// Created by georgerapeanu on 08.06.2022.
//

#ifndef MODEL_ISSUECONTROLLER_H
#define MODEL_ISSUECONTROLLER_H

#include "GeneralFileRepository.h"
#include "User.h"
#include "Issue.h"
#include <vector>

class IssueController{
    GeneralFileRepository<Issue> &issues;

public:

    IssueController(GeneralFileRepository<Issue> &issues);

    std::vector<Issue> getAllIssuesSortedByStatusAndDescription();

    void addIssue(const std::string &description, const User &reporter);

    void removeIssue(const std::string &description, const User &remover);

    void resolveIssue(const std::string &description, const User &resolver);
};

#endif //MODEL_ISSUECONTROLLER_H
