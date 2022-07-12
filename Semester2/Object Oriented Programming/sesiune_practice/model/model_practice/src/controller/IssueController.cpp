//
// Created by georgerapeanu on 08.06.2022.
//

#include "IssueController.h"
#include "Exceptions.h"
#include <algorithm>

IssueController::IssueController(GeneralFileRepository<Issue> &issues) :issues(issues){
    ;
}

std::vector<Issue> IssueController::getAllIssuesSortedByStatusAndDescription() {
    std::vector<Issue> answer = this->issues.getAll();
    std::sort(answer.begin(), answer.end(), [&](const Issue &first, const Issue &second){
        if(first.getStatus() != second.getStatus()){
            return first.getStatus() < second.getStatus();
        }
        return first.getDescription() < second.getDescription();
    });
    return answer;
}

void IssueController::addIssue(const std::string &description, const User &reporter) {
    if(reporter.getType() != "tester"){
        throw AppException("Only testers can add issues!");
    }
    if(description == ""){
        throw AppException("Descriptions can't be empty");
    }
    Issue issue(description, Issue::OPEN, reporter.getName(), "");
    this->issues.add(issue);
}

void IssueController::removeIssue(const std::string &description, const User &remover) {
    Issue issue(description, Issue::CLOSED, "", "");
    issue = this->issues.get(issue);
    if(issue.getStatus() != Issue::CLOSED){
        throw AppException("Only closed issues can be removed");
    }
    this->issues.remove(issue);
}

void IssueController::resolveIssue(const std::string &description, const User &resolver) {
    if(resolver.getType() != "programmer"){
        throw AppException("Only programmers can resolve issues!");
    }
    Issue issue(description, Issue::CLOSED, "", "");
    issue = this->issues.get(issue);
    if(issue.getStatus() != Issue::OPEN){
        throw AppException("Only open issues can be resolved");
    }
    issue.setSolver(resolver.getName());
    issue.setStatus(Issue::CLOSED);
    this->issues.update(issue);
}



