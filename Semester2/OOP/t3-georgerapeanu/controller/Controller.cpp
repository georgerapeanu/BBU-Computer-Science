//
// Created by georgerapeanu on 26.05.2022.
//

#include "Controller.h"
#include <algorithm>

Controller::Controller(FileRepository &repository):repository(repository){
    ;
}

std::vector<Document> Controller::get_all_documents_sorted_by_description_length_containing(std::string &s) {
    std::vector<Document> tmp = this->repository.get_all();
    std::sort(tmp.begin(), tmp.end(), [&](const Document &fst, const Document &snd){
        return fst.get_content().size() < snd.get_content().size();
    });
    std::vector<Document> ans;

    for(auto it:tmp){
        if(it.get_name().find(s) != std::string::npos ||
           it.get_keywords().find(s) != std::string::npos ||
           it.get_content().find(s) != std::string::npos){
            ans.push_back(it);
        }
    }
    return ans;
}

double Controller::get_similarity(const Document &a, std::string s) {
    /* This is left here in case you are supposed to get every substring of s and see the biggest one which is in a's keywords
    int ans = 0;
    for(int i = 0;i < (int)s.size();i++){
        for(int j = i;j < (int)s.size();j++){
            if(a.get_keywords().find(s.substr(i, j - i + 1)) != std::string::npos){
                ans = std::max(ans, j - i + 1);
            }
        }
    }
    return (double)ans / a.get_keywords().size();
     */
    if(a.get_keywords().find(s) != std::string::npos){
        return ((double)s.size()) / a.get_keywords().size();
    }
    return 0;
}
