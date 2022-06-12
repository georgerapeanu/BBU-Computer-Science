//
// Created by georgerapeanu on 08.06.2022.
//

#include <string>
#include <iostream>
#include "Issue.h"
#include "Exceptions.h"

const std::string &Issue::getDescription() const {
    return description;
}

void Issue::setDescription(const std::string &description) {
    Issue::description = description;
}

Issue::Status Issue::getStatus() const {
    return status;
}

void Issue::setStatus(Issue::Status status) {
    Issue::status = status;
}

const std::string &Issue::getReporter() const {
    return reporter;
}

void Issue::setReporter(const std::string &reporter) {
    Issue::reporter = reporter;
}

const std::string &Issue::getSolver() const {
    return solver;
}

void Issue::setSolver(const std::string &solver) {
    Issue::solver = solver;
}

Issue::Issue(const std::string &description, Issue::Status status, const std::string &reporter,
             const std::string &solver) : description(description), status(status), reporter(reporter),
                                          solver(solver) {}

std::ostream &operator<<(std::ostream &os, const Issue &issue) {
    os << issue.description << " " << (issue.status == Issue::OPEN ? "open":"closed") << " " << issue.reporter << " " << (issue.solver == "" ? "_":issue.solver);
    return os;
}

std::istream &operator>>(std::istream &is, Issue &issue){
    std::string status;
    is >> issue.description;
    is >> status;
    is >> issue.reporter >> issue.solver;
    if(!is){
        return is;
    }
    if(issue.solver == "_"){
        issue.solver = "";
    }
    if(status == "open"){
        issue.status = Issue::OPEN;
    }else if(status == "closed"){
        issue.status = Issue::CLOSED;
    }else{
        throw AppException("Invalid issue in file");
    }
    return is;
}

const std::string &Issue::getId() const {
    return this->description;
}

bool Issue::operator==(const Issue &other) const {
    return this->getId() == other.getId();
}

Issue::Issue() {
    ;
}
