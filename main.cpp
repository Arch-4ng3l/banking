#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

class Transfare {
private: 
	std::string direction;	
	std::string sender; 
	std::string recv; 
	int amount; 
public:
	Transfare(std::string dir, std::string s, std::string r, int a) {
	direction = dir; 
	sender = s; 
	recv = r; 
	amount = a; 
	}

	void printTransfare() {
		std::cout << "--------------------------------------------" << std::endl;
		std::cout << "type of Transaction: " << direction << std::endl;
		if (direction == "Send") {
			std::cout << "You send " << amount << "€ to " << recv << std::endl;
		} else {
			std::cout << "You received " << amount << "€ from " << sender << std::endl;
		}
		std::cout << "--------------------------------------------" << std::endl <<std::endl;
	}
};
class Account {
private:
  int balance;
  std::string name;
  std::string password;
	std::vector<Transfare> transfares;
public:
  Account() {
    std::cout << "Input Ure Name: ";
    std::cin >> name;
    std::cout << "Input ure Password: ";
    std::cin >> password;
    std::cout << "Input ure total Balance: ";
    std::cin >> balance;
		transfares.clear();
  }

  void withdraw(int amount) {
    if(amount > 0 && amount <= balance) {
      balance -= amount;
      std::cout << "U withdrawed: " << amount << "€" << std::endl;

    } else {

      std::cout << "U dont have enough money";
    }

  }

  void deposite() {

  }

  void printAccount() {
    std::cout << "Account Balance: " << balance << "€" << std::endl;
  }

  bool auth(const std::string& pw) {

    return pw == password;
  }

  std::string getName() {
    return name;
  }

  bool sendMoney(Account *acc, int amount) {
    if(balance < amount || amount < 0) {
      std::cout << "U dont have enough Money" << std::endl;
      return false;
    }
		Transfare t1 = Transfare("Send", name, acc->getName(), amount); 
		Transfare t2 = Transfare("Received", name, acc->getName(), amount); 
    acc->increaseBalance(amount);
		transfares.push_back(t1);
		acc->transfares.push_back(t2);
    balance-= amount;

    return true;
  }
	void seeAllTransfares() {
		if(transfares.size() == 0) {
			std::cout << "No Transactions Yet" << std::endl;
			return;
		}
		for(int i = 0; i < transfares.size(); i++) {
			std::cout << i+1 << std::endl << std::endl;
			transfares[i].printTransfare();
		}
	}
  void increaseBalance(int amount) {
    balance += amount;
  }

};

std::vector<Account> accountList;

void printMenu() {
    std::cout << "#########BANKING########"<< std::endl;
    std::cout << "#  1: Create Account   #" << std::endl;
    std::cout << "#  2: Sign in          #" << std::endl;
    std::cout << "#  3: Quit             #" << std::endl;
    std::cout << "########################"<< std::endl;
    std::cout << " => ";
}
void printAllAccounts() {

   for (int i = 0; i < accountList.size(); i++) {
    std::cout << "Account Number " << i + 1 << std::endl;
    accountList[i].printAccount();
    std::cout << std::endl;

   }
}
Account* findAccount(std::string name) {
  for(int i = 0; i < accountList.size(); i++) {
    if(name == accountList[i].getName())
      return &accountList[i];
  }
  return NULL;
}
Account* login() {
  std::string name;
  std::string pw;
  std::cout << "Name: ";
  std::cin >> name;
  Account* acc;
  for(int i = 0; i < accountList.size(); i++) {
    if(name == accountList[i].getName()) {
      acc = &accountList[i];
      break;
    }
  }
  std::cout << "Password: ";
  std::cin >> pw;
  if(acc->auth(pw)) {

	system("clear");
    return acc;
  } else {
    return NULL;
  }
}
void loggedIn(Account* acc) {
  while(1) {
    std::cout << "######### > " << acc->getName() << " < #########" << std::endl;
    std::cout << "#  1. See Account Value" << std::endl;
    std::cout << "#  2. Withdraw Money" << std::endl;
    std::cout << "#  3. Send Money" << std::endl;
    std::cout << "#  4. Deposite Money" << std::endl;
    std::cout << "#  5. Show all Transactions" << std::endl;
    std::cout << "#  6. Log out" << std::endl;
    std::cout << "######### > " << acc->getName() << " < #########"<< std::endl;

    int opt = 0;
    std::cin >> opt;
		switch(opt) {
		case 1:
			system("clear");
			acc->printAccount();
			break;
		case 2:
			system("clear");
			std::cout << "How much Money do u want to withdraw?" << std::endl;
			std::cin >> opt;
			acc->withdraw(opt);
			opt = 0;
			break;
		case 3: {
			system("clear");
			std::cout << "To which Account do u want to transfer the Money?" << std::endl;
			std::string search;
			std::cin >> search;
			Account* recv = findAccount(search);
			if(recv == nullptr) {
				std::cout << "couldnt Find Account" << std::endl;
				break;
			}
			std::cout << "How much Money" << std::endl << " => "; 
			std::cin >> opt;
			acc->sendMoney(recv, opt);
			opt = 0; 
			break;
		}
		case 4: 
			system("clear");
			acc->deposite();
			break;
		case 5: 
			system("clear");
			acc->seeAllTransfares();
			break;
		case 6:
			return;
		default: 
			system("clear");
			std::cout << "Invalid Option" << std::endl; 
			break;
	}

  }
}
int main(void) {
  system("clear");
  Account* acc;
  while(1) {

    int opt = 0;
    printMenu();

    std::cin >> opt;

    switch (opt) {
    case 1:
			system("clear");
      accountList.push_back(Account());
      break;
    case 2:
			system("clear");
      acc = login();
      if (acc == NULL) {
        std::cout << "Login failed" << std::endl;
      } else {
        loggedIn(acc);
      }
      break;

    case 3:
      return 0;
    }
  }

  return 0;
}
