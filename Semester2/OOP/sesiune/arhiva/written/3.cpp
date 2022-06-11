#include <bits/stdc++.h>

using namespace std;

class Channel{
public:
  virtual void send(const string &message) = 0;
};

class Telephone : public Channel{
  string number;

public:
  
  Telephone(const string &number) : number(number) {
    ;
  }
  
  virtual void send(const string &message)override{
    cout << "dialing " + number << "\n";
    int tmp = rand() % 10;
    cerr << "random is " << tmp << "\n";
    if(tmp % 10 == 0){
      throw exception();
    }
  }
};

class SMS : public Telephone{
public:

  SMS(const string& message) : Telephone(message){
    ;
  }

  virtual void send(const string& message)override{
    cerr << "SMS::send" << "\n";
    Telephone::send(message);
    cout << "sending sms\n";
  }
};

class Fax : public Telephone{
public:
  Fax(const string& message) : Telephone(message){
    ;
  }
  virtual void send(const string& message)override{
    cerr << "Fax::send" << "\n";
    Telephone::send(message);
    cout << "sending fax\n";
  }
};

class Failover : public Channel {
  Channel* channel1, *channel2;

public:
  
  Failover(Channel* channel1, Channel* channel2) : channel1(channel1), channel2(channel2) {
    ;
  }
  
  virtual void send(const string& message)override{
    try{
      cerr << "Failover::send1" << "\n";
      channel1->send(message);
    }catch(const exception &ex){
      cerr << "Failover::send2" << "\n";
      channel2->send(message);
    }
  }
};

class Contact : public Channel{
  
  Channel* channel1, *channel2, *channel3;

public:
  
  Contact(Channel* channel1, Channel* channel2, Channel* channel3) : channel1(channel1), channel2(channel2), channel3(channel3) {
    ;
  }
  
  void sendAlarm(const string& message){
    try{
      cerr << "Contact::send1" << "\n";
      channel1->send(message);
    }catch(const exception &ex){
      try{
        cerr << "Contact::send2" << "\n";
        channel2->send(message);
      }catch(const exception &ex){
        cerr << "Contact::send3" << "\n";
        channel3->send(message);
      }
    }
  }

  virtual void send(const string& message)override{
    this->sendAlarm(message);
  }
};


int main(){
    srand(time(NULL));

  Channel* channel = new Contact(new Telephone("0123"), new Failover(new Fax("0123"), new SMS("0123")), new Contact(new Telephone("0123"), new Fax("0123"), new SMS("0123")));

 channel->send("");
 
  
  return 0;
}

