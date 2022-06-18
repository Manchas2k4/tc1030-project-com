// =========================================================
// File: main.cpp
// Author: Uri Jared Gopar Morales- A01709413
// Date: 16/06/2022
// Description:En este archivo se encuentra la función main la cual va a
// tener como objetivo llamar a todos los los resultados obtenidos por medio de las clases.
// To compile: g++ -std=c++11 main.cpp -o app
// To execute: ./app input_file output_file
// =========================================================
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bill.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "customer.h"
#include <list>
//2 <type> si es 1 es vox y 2 internet<talkingCharge> <messageCost> <networkCharge> <discountRate>
using namespace std;

int main(int argc, char* argv[]) {
  ifstream inputFile;
  ofstream outputFile;
  int c,o,n,age,OperatorId,opType,discountRate,idCustomer1,idCustomer2,time,quantity,idCustomer,op,idOperator;
  double limitngAmount,talkingCharge,messageCost,networkCharge,amount;
  string name;
  vector<Customer *>Cus;
  vector<Operator *>Ope;

  if (argc != 3) {
    cout << "usage: " << argv[0] << " input_file output_file\n";
    return -1;
  }

  inputFile.open(argv[1]);
  if (!inputFile.is_open()) {
    cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }

  outputFile.open(argv[2]);

  inputFile >> c>>o>>n;
  Cus.resize(c);
  Ope.resize(o);
  int cus_conteo=0;
  int ope_conteo=0;
  for (int i = 0; i < n; i++) {
        inputFile>>op;

    switch(op) {
      case 1:inputFile>>name>>age>>OperatorId>>limitngAmount;
        Cus[cus_conteo]= new Customer (cus_conteo,name,age,Ope[OperatorId],limitngAmount);
        cus_conteo++;

        break;
      case 2:inputFile>>opType>>talkingCharge>>messageCost>>networkCharge>>discountRate;
        if(opType==1){
            Ope[ope_conteo]=new VoxOperator (ope_conteo,talkingCharge,messageCost,networkCharge,discountRate,VOX);
        }
        if(opType==2){
            Ope[ope_conteo]=new InternetOperator(ope_conteo,talkingCharge,messageCost,networkCharge,discountRate,INTERNET);
        }
        ope_conteo++;
        break;

      case 3:inputFile>>idCustomer1>>idCustomer2>>time;
        Cus[idCustomer1]->talk(time,*Cus[idCustomer2]);
        break;
      case 4:inputFile>>idCustomer1>>idCustomer2>>quantity;
        Cus[idCustomer1]->message(quantity,*Cus[idCustomer2]);
          break;
      case 5:inputFile>>idCustomer>>amount;
        Cus[idCustomer]->connection(amount);
          break;
      case 6:inputFile>>idCustomer>>amount;
        Cus[idCustomer]->pay(amount);

          break;
      case 7:inputFile>>idCustomer>>idOperator;
        Cus[idCustomer]->setOperator(Ope[idOperator]);
        break;
      case 8:inputFile>>idCustomer>>amount;
        Cus[idCustomer]->getBill()->changeTheLimit(amount);
        break;
    }

  }
   for (int i=0; i<ope_conteo;i++){
   outputFile<<Ope[i]->toString();
  }

  for (int i=0; i<cus_conteo;i++){
   outputFile<<Cus[i]->toString();
  }
  int id=0;
  double maximo=Cus[0]->getTotalSpentTalkingTime();
  for (int i=0; i<cus_conteo;i++){
    if(Cus[i]->getTotalSpentTalkingTime()>maximo){
        maximo=Cus[i]->getTotalSpentTalkingTime();
        id=i;
    }
  }
  outputFile<<Cus[id]->getName()<<": "<<maximo;
  outputFile<<"\n";
  id=0;
  double maximoM=Cus[0]->getTotalMessageSent();
  for (int i=0; i<cus_conteo;i++){
    if(Cus[i]->getTotalMessageSent()>maximoM){
        maximoM=Cus[i]->getTotalMessageSent();
        id=i;
    }
  }
  outputFile<<Cus[id]->getName()<<": "<<maximoM;

  outputFile<<"\n";
  id=0;
  double maximoG=Cus[0]->getTotalInternetUsage();
  for (int i=0; i<cus_conteo;i++){
    if(Cus[i]->getTotalInternetUsage()>maximoG){
        maximoG=Cus[i]->getTotalInternetUsage();
        id=i;
    }
  }
  outputFile<<Cus[id]->getName()<<": "<<maximoG;

  for(id=0;id<o;id++){
    delete Ope[id];
  }
  for(id=0;id<c;id++){
    delete Cus[id];
  }

  inputFile.close();
  outputFile.close();
  return 0;
}
