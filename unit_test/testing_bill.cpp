// =========================================================
// File: testing_bill.cpp
// Author: Dr. Pedro O. Perez-Murueta
// Date: 4/Jan/2022
// Description: This file contains the series of tests that
//							the Bill class must pass.
// To compile: g++ -std=c++11 testing_bill.cpp -o app
// To execute: ./app
// =========================================================
#define CATCH_CONFIG_MAIN
#include <string>
#include "catch.h"
#include "../bill.h"

TEST_CASE("testing default constructor", "[Bill()]") {
	Bill b;

	REQUIRE(b.getLimitAmount() == 0.0);
	REQUIRE(b.getCurrentDebt() == 0.0);
  REQUIRE(b.getTotalMoneySpent() == 0.0);
}

TEST_CASE("testing constructor with a positivo amount",
	"[Bill(amount)]") {
	Bill b(100.0);

	REQUIRE(b.getLimitAmount() == 100.0);
	REQUIRE(b.getCurrentDebt() == 0.0);
  REQUIRE(b.getTotalMoneySpent() == 0.0);
}

TEST_CASE("testing constructor with a negativo amount",
	"[Bill(amount)]") {
	Bill b(-100.0);

	REQUIRE(b.getLimitAmount() == 0.0);
	REQUIRE(b.getCurrentDebt() == 0.0);
  REQUIRE(b.getTotalMoneySpent() == 0.0);
}

TEST_CASE("testing check", "[check]") {
	Bill b(100.0);

	REQUIRE(b.check(50.0) == true);
  REQUIRE(b.check(150.0) == false);
}

TEST_CASE("testing add", "[add]") {
	Bill b(100.0);

	b.add(50.0);
	REQUIRE(b.getCurrentDebt() == 50.0);
	b.add(-50.0);
  REQUIRE(b.getCurrentDebt() == 50.0);
}

TEST_CASE("testing pay", "[pay]") {
	Bill b(100.0);

	b.add(50.0);
	b.pay(20.0);
	REQUIRE(b.getCurrentDebt() == 30.0);
	REQUIRE(b.getTotalMoneySpent() == 20.0);
	b.pay(-10.0);
	REQUIRE(b.getCurrentDebt() == 30.0);
	REQUIRE(b.getTotalMoneySpent() == 20.0);
	b.pay(100.0);
	REQUIRE(b.getCurrentDebt() == 00.0);
	REQUIRE(b.getTotalMoneySpent() == 50.0);
}

TEST_CASE("testing copy constructor", "[Bill(const Bill&)]") {
	Bill b(100.0);
	b.add(50.0);
	b.pay(20.0);

	Bill a(b);

	REQUIRE(a.getCurrentDebt() == 30.0);
	REQUIRE(a.getTotalMoneySpent() == 20.0);
}
