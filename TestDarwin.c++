#include "gtest/gtest.h"

#include "Darwin.h"
#include <iostream>
#include <sstream>
#include <string>

// ------------
// SpeciesTest
// ------------

// TEST(SpeciesTest, species_1) {

//     ASSERT_TRUE(true);
// }

// TEST(SpeciesTest, species_2) {

//     ASSERT_TRUE(true);
// }

// TEST(SpeciesTest, species_3) {

//     ASSERT_TRUE(true);
// }
// TEST(SpeciesTest, addInstruction_1){
    
// }

// TEST(SpeciesTest, addInstruction_2){
    
// }

// TEST(SpeciesTest, addInstruction_3){
    
// }

// TEST(SpeciesTest, print_name_1){
    
// }

// TEST(SpeciesTest, print_name_2){
    
// }

// TEST(SpeciesTest, print_name_3){
    
// }

// TEST(SpeciesTest, equal_1){
    
// }

// TEST(SpeciesTest, equal_2){
    
// }

// TEST(SpeciesTest, equal_3){
    
// }

// TEST(SpeciesTest, remove_1){
    
// }

// TEST(SpeciesTest, remove_2){
    
// }

// TEST(SpeciesTest, remove_3){
    
// }

// TEST(SpeciesTest, print_1){
    
// }

// TEST(SpeciesTest, print_2){
    
// }

// TEST(SpeciesTest, print_3){
    
// }

// TEST(SpeciesTest, get_action_1){
    
// }

// TEST(SpeciesTest, get_action_2){
    
// }

// TEST(SpeciesTest, get_action_3){
    
// }

// ------------
// CreatureTest
// ------------

// TEST(CreatureTest, do_inst_1){

// }
// TEST(CreatureTest, do_inst_2){

// }
// TEST(CreatureTest, do_inst_3){

// }
// TEST(CreatureTest, is_empty_1){

// }
// TEST(CreatureTest, is_empty_2){

// }
// TEST(CreatureTest, is_empty_3){

// }
// TEST(CreatureTest, is_wall_1){

// }
// TEST(CreatureTest, is_wall_2){

// }
// TEST(CreatureTest, is_wall_3){

// }
// TEST(CreatureTest, ex_go_1){

// }
// TEST(CreatureTest, ex_go_2){

// }   
// TEST(CreatureTest, ex_go_3){

// }   
// TEST(CreatureTest, ex_hop_1){

// }
// TEST(CreatureTest, ex_hop_2){

// }
// TEST(CreatureTest, ex_hop_3){

// }
// TEST(CreatureTest, ex_left_1){

// }
// TEST(CreatureTest, ex_left_2){

// }
// TEST(CreatureTest, ex_left_3){

// }
// TEST(CreatureTest, ex_right_1){

// }
// TEST(CreatureTest, ex_right_2){

// }
// TEST(CreatureTest, ex_right_3){

// }
// TEST(CreatureTest, ex_infect_1){

// }
// TEST(CreatureTest, ex_infect_2){

// }
// TEST(CreatureTest, ex_infect_3){

// }
// TEST(CreatureTest, ex_if_empty_1){

// }
// TEST(CreatureTest, ex_if_empty_2){

// }
// TEST(CreatureTest, ex_if_empty_3){

// }
// TEST(CreatureTest, ex_if_wall_1){

// }
// TEST(CreatureTest, ex_if_wall_2){

// }
// TEST(CreatureTest, ex_if_wall_3){

// }
// TEST(CreatureTest, ex_if_random_1){

// }
// TEST(CreatureTest, ex_if_random_2){

// }
// TEST(CreatureTest, ex_if_random_3){

// }
// TEST(CreatureTest, ex_if_enemy_1){

// }
// TEST(CreatureTest, ex_if_enemy_2){

// }
// TEST(CreatureTest, ex_if_enemy_3){

// }

// Public methods

// TEST(CreatureTest, creature_1) {

//     ASSERT_TRUE(true);
// }
// TEST(CreatureTest, creature_2) {

//     ASSERT_TRUE(true);
// }
// TEST(CreatureTest, creature_3) {

//     ASSERT_TRUE(true);
// }
// TEST(CreatureTest, execute_instr_1) {

//     ASSERT_TRUE(true);
// }
// TEST(CreatureTest, execute_instr_2) {

//     ASSERT_TRUE(true);
// }
// TEST(CreatureTest, execute_instr_3) {

//     ASSERT_TRUE(true);
// }

// TEST(CreatureTest, print_species_1) {

//     ASSERT_TRUE(true);
// }

// TEST(CreatureTest, print_species_2) {

//     ASSERT_TRUE(true);
// }

// TEST(CreatureTest, print_species_3) {

//     ASSERT_TRUE(true);
// }

// TEST(CreatureTest, is_creature_1) {

//     ASSERT_TRUE(true);
// }

// TEST(CreatureTest, is_creature_2) {

//     ASSERT_TRUE(true);
// }

// TEST(CreatureTest, is_creature_3) {

//     ASSERT_TRUE(true);
// }

// TEST(CreatureTest, remove_1) {

//     ASSERT_TRUE(true);
// }

// TEST(CreatureTest, remove_2) {

//     ASSERT_TRUE(true);
// }

// TEST(CreatureTest, remove_3) {

//     ASSERT_TRUE(true);
// }


// Do we want print function?
// TEST(CreatureTest, print_1) {

//     ASSERT_TRUE(true);
// }

// TEST(CreatureTest, print_2) {

//     ASSERT_TRUE(true);
// }

// TEST(CreatureTest, print_3) {

//     ASSERT_TRUE(true);
// }

// ----------
// DarwinTest
// ----------

TEST(DarwinTest, darwin_1) {

    ASSERT_TRUE(true);
}

TEST(DarwinTest, darwin_2) {

    ASSERT_TRUE(true);
}

TEST(DarwinTest, darwin_3) {

    ASSERT_TRUE(true);
}

TEST(DarwinTest, add_creature_1) {
    Darwin d = Darwin(7, 7);
    Species t = Species("trap");
    Creature t1 = Creature(t, south);
    d.addCreature(t1, 0, 0);
    Creature temp = d.at(0, 0);
    ASSERT_TRUE(temp.is_creature());
}

TEST(DarwinTest, add_creature_2) {
    Darwin d = Darwin(10, 10);
    Species f = Species("food");
    Creature f1 = Creature(f, north);
    d.addCreature(f1, 2, 2);
    Creature temp = d.at(2, 2);
    ASSERT_TRUE(temp.is_creature());

    ostringstream w;
    temp.print_species(w);

    ASSERT_EQ("f", w.str());
}

TEST(DarwinTest, add_creature_3) {
    Darwin d = Darwin(10, 10);
    Species f = Species("food");
    Creature f1 = Creature(f, north);

    Species h = Species("hopper");
    Creature h1 = Creature(h, east);

    Species r = Species("rover");
    Creature r1 = Creature(r, west);
    Creature r2 = Creature(r, west);
    d.addCreature(f1, 1, 1);
    d.addCreature(h1, 3, 4);
    d.addCreature(r1, 5, 7);

    ASSERT_TRUE(d.at(1, 1).is_creature());
    ASSERT_TRUE(d.at(3, 4).is_creature());
    ASSERT_TRUE(d.at(5, 7).is_creature());
    ASSERT_FALSE(d.at(0, 0).is_creature());

    ostringstream w;
    d.at(1, 1).print_species(w);
    d.at(3, 4).print_species(w);
    d.at(5, 7).print_species(w);
    ASSERT_EQ("fhr", w.str());


    // d.addCreature(r2, 11, 11);
}

// TEST(DarwinTest, at_1) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }
// TEST(DarwinTest, at_2) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }
// TEST(DarwinTest, at_3) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, begin_1) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, begin_2) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, begin_3) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, end_1) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, end_2) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, end_3) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, turn_1) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, turn_2) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }
// TEST(DarwinTest, turn_3) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, print_1) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, print_2) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, print_3) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, simulation_1) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, simulation_2) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }

// TEST(DarwinTest, simulation_3) {
//     Darwin d2 = Darwin(7, 9);
//     int s = d2.board.size();
//     ASSERT_EQ(s, 7);
// }
