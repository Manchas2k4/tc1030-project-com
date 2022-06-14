// =========================================================
// File: testing_op.cpp
// Author: Pedro O. Perez-Murueta, Phd.
// Date: 4/Jan/2022
// Description: This file contains the series of tests that
//              the InternetOperator class must pass.
// To compile: g++ -std=c++11 testing_internet.cpp -o app
// To execute: ./app
// =========================================================
#define CATCH_CONFIG_MAIN
#include <string>
#include "catch.h"
#include "../internet.h"

TEST_CASE("testing default constructor",
  "[InternetOperator(int, double, double, double, int, OperatorType)]") {
	InternetOperator op(1, 10.00, 10.00, 10.00, 10, INTERNET);

	REQUIRE(op.getId() == 1);
  REQUIRE(op.getDiscountRate() == 10);
  REQUIRE(op.getTalkingChage() == 10.0);
  REQUIRE(op.getMessageCost() == 10.0);
  REQUIRE(op.getNetworkCharge() == 10.0);
  REQUIRE(op.getTotalSpentTalkingTime() == 0);
  REQUIRE(op.getTotalMessageSent() == 0);
  REQUIRE(op.getTotalInternetUsage() == 0);
  REQUIRE(op.getType() == INTERNET);
}

TEST_CASE("testing to add call minutes", "[addTalkingTime(int)]") {
	InternetOperator op(1, 10.00, 10.00, 10.00, 10, INTERNET);

  op.addTalkingTime(-10);
  REQUIRE(op.getTotalSpentTalkingTime() == 0);
	op.addTalkingTime(10);
  REQUIRE(op.getTotalSpentTalkingTime() == 10);
}

TEST_CASE("testing to add sents messages", "[addTotalMessageSent(int)]") {
	InternetOperator op(1, 10.00, 10.00, 10.00, 10, INTERNET);

  op.addTotalMessageSent(-10);
  REQUIRE(op.getTotalMessageSent() == 0);
	op.addTotalMessageSent(10);
  REQUIRE(op.getTotalMessageSent() == 10);
}

TEST_CASE("testing to add used MB", "[addTotalInternetUsage(double)]") {
	InternetOperator op(1, 10.00, 10.00, 10.00, 10, INTERNET);

  op.addTotalInternetUsage(-10);
  REQUIRE(op.getTotalInternetUsage() == 0);
	op.addTotalInternetUsage(10);
  REQUIRE(op.getTotalInternetUsage() == 10);
}

TEST_CASE("testing call calculation", "[calculateTalkingCost(int, int)]") {
	InternetOperator op(1, 10.00, 10.00, 10.00, 10, INTERNET);

  REQUIRE(op.calculateTalkingCost(-10, 40) == 0);
	REQUIRE(op.calculateTalkingCost(10, 40) == 100);
  REQUIRE(op.calculateTalkingCost(1, 15) == 9);
}

TEST_CASE("testing the calculation by sending messages",
  "[calculateMessageCost(int, int, int)]") {
	InternetOperator op(1, 10.00, 10.00, 10.00, 10, INTERNET);

  REQUIRE(op.calculateMessageCost(-10, 1, 3) == 0);
	REQUIRE(op.calculateMessageCost(10, 1, 3) == 100);
  REQUIRE(op.calculateMessageCost(2, 1, 1) == 18);
}

TEST_CASE("testing calculation by internet usage",
  "[calculateNetworkCost(double)]") {
	InternetOperator op(1, 10.00, 10.00, 10.00, 10, INTERNET);

	REQUIRE(op.calculateNetworkCost(-10) == 0);
  REQUIRE(op.calculateNetworkCost(10) == 90);
  op.addTotalInternetUsage(10);
  REQUIRE(op.calculateNetworkCost(10) == 90);
}

TEST_CASE("testing copy constructor",
  "[op(const op&)]") {
	InternetOperator op(1, 10.00, 10.00, 10.00, 10, INTERNET);
  op.addTotalMessageSent(10);
  op.addTalkingTime(200);
  op.addTotalInternetUsage(53);

  InternetOperator b(op);
	REQUIRE(b.getId() == 1);
  REQUIRE(b.getDiscountRate() == 10);
  REQUIRE(b.getTalkingChage() == 10.0);
  REQUIRE(b.getMessageCost() == 10.0);
  REQUIRE(b.getNetworkCharge() == 10.0);
  REQUIRE(b.getTotalSpentTalkingTime() == 200);
  REQUIRE(b.getTotalMessageSent() == 10);
  REQUIRE(b.getTotalInternetUsage() == 53);
  REQUIRE(b.getType() == INTERNET);
}
