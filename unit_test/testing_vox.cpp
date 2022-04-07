// =========================================================
// File: testing_vox.cpp
// Author: Pedro O. Perez-Murueta, Phd.
// Date: 4/Jan/2022
// Description: This file contains the series of tests that the
//							VoxOperator class must pass.
// To compile: g++ -std=c++11 testing_vox.cpp -o app
// To execute: ./app
// =========================================================
#define CATCH_CONFIG_MAIN
#include <string>
#include "catch.h"
#include "../vox.h"

TEST_CASE("testing default constructor",
  "[Vox(int, double, double, double, int, OperatorType)]") {
	VoxOperator vox(1, 10.00, 10.00, 10.00, 10, VOX);

	REQUIRE(vox.getId() == 1);
  REQUIRE(vox.getDiscountRate() == 10);
  REQUIRE(vox.getTalkingChage() == 10.0);
  REQUIRE(vox.getMessageCost() == 10.0);
  REQUIRE(vox.getNetworkCharge() == 10.0);
  REQUIRE(vox.getTotalSpentTalkingTime() == 0);
  REQUIRE(vox.getTotalMessageSent() == 0);
  REQUIRE(vox.getTotalInternetUsage() == 0);
  REQUIRE(vox.getType() == VOX);
}

TEST_CASE("testing to add call minutes", "[addTalkingTime(int)]") {
	VoxOperator vox(1, 10.00, 10.00, 10.00, 10, VOX);

  vox.addTalkingTime(-10);
  REQUIRE(vox.getTotalSpentTalkingTime() == 0);
	vox.addTalkingTime(10);
  REQUIRE(vox.getTotalSpentTalkingTime() == 10);
}

TEST_CASE("testing to add sents messages", "[addTotalMessageSent(int)]") {
	VoxOperator vox(1, 10.00, 10.00, 10.00, 10, VOX);

  vox.addTotalMessageSent(-10);
  REQUIRE(vox.getTotalMessageSent() == 0);
	vox.addTotalMessageSent(10);
  REQUIRE(vox.getTotalMessageSent() == 10);
}

TEST_CASE("testing to add used MB", "[addTotalInternetUsage(double)]") {
	VoxOperator vox(1, 10.00, 10.00, 10.00, 10, VOX);

  vox.addTotalInternetUsage(-10);
  REQUIRE(vox.getTotalInternetUsage() == 0);
	vox.addTotalInternetUsage(10);
  REQUIRE(vox.getTotalInternetUsage() == 10);
}

TEST_CASE("testing call calculation", "[calculateTalkingCost(int, int)]") {
	VoxOperator vox(1, 10.00, 10.00, 10.00, 10, VOX);

  REQUIRE(vox.calculateTalkingCost(-10, 40) == 0);
  REQUIRE(vox.calculateTalkingCost(10, -40) == 0);
	REQUIRE(vox.calculateTalkingCost(10, 40) == 100);
  REQUIRE(vox.calculateTalkingCost(10, 15) == 90);
}

TEST_CASE("testing the calculation by sending messages",
  "[calculateMessageCost(int, int, int)]") {
	VoxOperator vox(1, 10.00, 10.00, 10.00, 10, VOX);

  REQUIRE(vox.calculateMessageCost(-10, 1, 3) == 0);
	REQUIRE(vox.calculateMessageCost(10, 1, 3) == 100);
  REQUIRE(vox.calculateMessageCost(10, 1, 1) == 90);
}

TEST_CASE("testing calculation by internet usage",
  "[calculateNetworkCost(double)]") {
	VoxOperator vox(1, 10.00, 10.00, 10.00, 10, VOX);

	REQUIRE(vox.calculateNetworkCost(-10) == 0);
  REQUIRE(vox.calculateNetworkCost(10) == 100);
}

TEST_CASE("testing copy constructor",
  "[Vox(const Vox&)]") {
	VoxOperator vox(1, 10.00, 10.00, 10.00, 10, VOX);
  vox.addTotalMessageSent(10);
  vox.addTalkingTime(200);
  vox.addTotalInternetUsage(53);

  VoxOperator b(vox);
	REQUIRE(b.getId() == 1);
  REQUIRE(b.getDiscountRate() == 10);
  REQUIRE(b.getTalkingChage() == 10.0);
  REQUIRE(b.getMessageCost() == 10.0);
  REQUIRE(b.getNetworkCharge() == 10.0);
  REQUIRE(b.getTotalSpentTalkingTime() == 200);
  REQUIRE(b.getTotalMessageSent() == 10);
  REQUIRE(b.getTotalInternetUsage() == 53);
  REQUIRE(b.getType() == VOX);
}
