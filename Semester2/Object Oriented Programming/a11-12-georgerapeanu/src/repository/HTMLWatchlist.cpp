/*!
 * @file HTMLWatchlist.h this is a file that shows the implementation for a HTMLWatchlist
 */


//
// Created by georgerapeanu on 18.04.2022.
//


#pragma once
#include "HTMLWatchlist.h"
#include "Movie.h"
#include "Exceptions.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

template<class T>
HTMLWatchlist<T>::HTMLWatchlist(const string &file_path) {
    this->file_path = file_path;
    this->entities = vector<T>();
}

template<class T>
HTMLWatchlist<T>::~HTMLWatchlist() {
    ;
}

template<class T>
void HTMLWatchlist<T>::add(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            throw RepositoryException("Id already exists");
        }
    }
    this->entities.push_back(elem);
    this->save();
}

template<class T>
void HTMLWatchlist<T>::update(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            this->entities[i] = elem;
            this->save();
            return ;
        }
    }
    throw RepositoryException("Id doesn't exist");
}


template<class T>
void HTMLWatchlist<T>::remove(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            this->entities.erase(this->entities.begin() + i);
            this->save();
            return ;
        }
    }
    throw RepositoryException("Id doesn't exist");
}

template<class T>
T HTMLWatchlist<T>::find(const T &elem) {
    for(int i = 0;i < this->entities.size();i++){
        if(this->entities[i].get_id() == elem.get_id()){
            return this->entities[i];
        }
    }
    throw RepositoryException("Id doesn't exist");
}

template<class T>
vector<T> HTMLWatchlist<T>::get_all() {
    return this->entities;
}

template<class T>
void HTMLWatchlist<T>::save() const {
    ofstream fout(this->file_path);
    fout << "<!DOCTYPE html>" << endl;
    fout << "<html>" << endl;
    fout << "<head>" << endl;
    fout << "\t<title>Movie watchlist </title>" << endl;
    fout << "</head>" << endl;
    fout << "<body>" << endl;
    fout << "<table border=\"1\">" << endl;
    fout << "\t<tr>" << endl;
    fout << "\t\t<td>Title</td>" << endl;
    fout << "\t\t<td>Genre</td>" << endl;
    fout << "\t\t<td>Year</td>" << endl;
    fout << "\t\t<td>Likes</td>" << endl;
    fout << "\t\t<td>Trailer link</td>" << endl;
    fout << "\t</tr>" << endl;

    for(const Movie &entity:entities){
        fout << "\t<tr>" << endl;
        fout << "\t\t<td>" << entity.get_title() << "</td>" << endl;
        fout << "\t\t<td>" << entity.get_genre() << "</td>" << endl;
        fout << "\t\t<td>" << entity.get_year() << "</td>" << endl;
        fout << "\t\t<td>" << entity.get_likes() << "</td>" << endl;
        fout << "\t\t<td><a href=" << entity.get_trailer_link() << ">Link</a></td>" << endl;
        fout << "\t</tr>" << endl;
    }
    fout << "</table>" << endl;
    fout << "</body>" << endl;
    fout << "</html>" << endl;
    fout.close();
}

template<class T>
void HTMLWatchlist<T>::display() const {
    system(("firefox " + this->file_path).c_str());
}

template class HTMLWatchlist<Movie>;
