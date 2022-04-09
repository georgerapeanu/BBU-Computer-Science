//
// Created by georgerapeanu on 07.04.2022.
//

#include "utils.h"

using namespace std;

vector<string> utils::split_string(string s, char delim) {
    vector<string> ans;

    string curr = "";

    for(auto it:s){
        if(it == delim){
            if(curr != ""){
                ans.push_back(curr);
            }
            curr="";
        }else{
            curr += it;
        }
    }
    if(curr != ""){
        ans.push_back(curr);
    }
    return ans;
}
