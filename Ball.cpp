#include "Ball.h"

uint8_t Ball::distance_to_field_boundary (Player &player) {
  if ( position > 29 ) {
    return position - player.hitbox_min;
  } else {
    return player.hitbox_max - position;
  }
}

// convert speed (in m/s) to timer delay
uint16_t Ball::speed_to_timer() {
  double s = speed + speedup;
  //return (uint16_t)((STRIPE_LENGTH*1000.0) / (NUM_LEDS*s));
  return (uint16_t)((1.0*1000.0) / (60*s));
}

void Ball::reverse_direction() {
  direction *= -1;
}

void Ball::increase_speed() {
  speed *= 1.05;
}

Ball::Ball(int8_t position, uint8_t min_position, uint8_t max_position, double speed, int8_t direction) {
//  init(0,0.2,1);
  this->position = position;
  this->min_position = min_position;
  this->max_position = max_position;
  this->speed = speed;
  this->direction = direction;
}

bool Ball::is_inside_hitbox(Player &player) {
  if ( player.hitbox_min <= position && position <= player.hitbox_max ) {
    return true;
  }
  return false;
}

bool Ball::timer() {
  if ( millis() - time >= speed_to_timer() ) {
    time = millis();
    return true;
  }
  return false;
}

int8_t Ball::get_position() {
  return position;
}

int8_t Ball::get_previous_position() {
  return previous_position;
}

void Ball::set_position(int8_t p) {
  position = p;
}

int8_t Ball::get_direction() {
  return direction;
}

void Ball::hit() {
  reverse_direction();
  increase_speed();
}

void Ball::calc_speedup(Player p) {
  speedup = distance_to_field_boundary(p)/10.0;
}

void Ball::advance() {
  previous_position = position;
  position += direction;
}

/*
void Ball::advance() {
  leds[b.get_position()] = CRGB::Black;
  
  draw_player_score(p1);
  draw_player_score(p2);
  
  b.set_position(b.get_position() + b.get_direction());
  leds[b.get_position()] = CRGB::White;
}
*/