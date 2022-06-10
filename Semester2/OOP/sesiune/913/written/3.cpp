#include <bits/stdc++.h>

using namespace std;

class Action{
public:
  virtual void execute() = 0;
};

class CreateAction : public Action {
public:
  virtual void execute(){
    cout << "Create file ";
  }
};

class ExitAction : public Action {
public:
  virtual void execute(){
    cout << "Exit application ";
  }
};

class MenuItem{
  Action* action;
  string text;

  public:

  virtual void print(){
    cout << text << " ";
  }

  virtual void clicked(){
    if(action != NULL){
      action->execute();
    }
  }

  MenuItem(string text, Action* action = NULL){
    this->text = text;
    this->action = action;
  }

  virtual ~MenuItem(){
    ;///shouldnt delete action because it is association
  }
};

class Menu : public MenuItem{
  vector<MenuItem*> items;
  public:
  virtual ~Menu(){
    ;///shouldnt delete action because its aggregation
  }

  Menu(string text, Action* action = NULL) : MenuItem(text, action){
    ;
  }

  void add(MenuItem* item){
    items.push_back(item);
  }

  virtual void print(){
    MenuItem::print();
    for(auto it:items){
      it->print();
    }
  }
};

class MenuBar{
  vector<Menu*> menus;
public:
  void add(Menu* menu){
    menus.push_back(menu);
  }
  void print(){
    for(auto it:menus){
      it->print();
    }
  }
};

int main(){

  MenuBar* bar = new MenuBar();
  Menu* file_menu = new Menu("File", NULL);
  Menu* about_menu = new Menu("About", NULL);
  Menu* new_menu = new Menu("New", NULL);
  ExitAction* exit_menu_action = new ExitAction();
  Menu* exit_menu = new Menu("Exit", exit_menu_action);
  CreateAction* text_menu_action = new CreateAction();
  Menu* text_menu = new Menu("Text",text_menu_action);
  CreateAction* cpp_menu_action = new CreateAction();
  Menu* cpp_menu = new Menu("C++", cpp_menu_action);

  new_menu->add(text_menu);
  new_menu->add(cpp_menu);
  file_menu->add(new_menu);
  file_menu->add(exit_menu);
  bar->add(file_menu);
  bar->add(about_menu);
  
  file_menu->print();
  file_menu->clicked();
  new_menu->print();
  new_menu->clicked();
  cpp_menu->print();
  cpp_menu->clicked();
 
  delete cpp_menu;
  delete cpp_menu_action;
  delete text_menu;
  delete text_menu_action;
  delete exit_menu;
  delete exit_menu_action;
  delete new_menu;
  delete about_menu;
  delete file_menu;
  delete bar;

  return 0;
}


