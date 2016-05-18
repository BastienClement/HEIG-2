//
// Created by Bastien Clément on 18.05.16.
//

#include "PersonVisitor.h"

void PersonVisitor::visit(const FamilyMember&) { }

void PersonVisitor::visit(const Child& child) {
	visit((FamilyMember&) child);
}

void PersonVisitor::visit(const Parent& parent) {
	visit((FamilyMember&) parent);
}

void PersonVisitor::visit(const Boy& boy) {
	visit((Child&) boy);
}

void PersonVisitor::visit(const Girl& girl) {
	visit((Child&) girl);
}

void PersonVisitor::visit(const Father& father) {
	visit((Parent&) father);
}

void PersonVisitor::visit(const Mother& mother) {
	visit((Parent&) mother);
}

void PersonVisitor::visit(const Cop&) { }

void PersonVisitor::visit(const Thief&) { }
