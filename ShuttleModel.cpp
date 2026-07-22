#include "ShuttleModel.h"

int SmallShuttleModel::getMaxSeats() const { return 2; }
string SmallShuttleModel::getName() const { return "Small Shuttle"; }
unique_ptr<ShuttleModel> SmallShuttleModel::clone() const { return make_unique<SmallShuttleModel>(); }

int FamilyShuttleModel::getMaxSeats() const { return 5; }
string FamilyShuttleModel::getName() const { return "Family Shuttle"; }
unique_ptr<ShuttleModel> FamilyShuttleModel::clone() const { return make_unique<FamilyShuttleModel>(); }

int PremiumShuttleModel::getMaxSeats() const { return 12; }
string PremiumShuttleModel::getName() const { return "Premium Shuttle"; }
unique_ptr<ShuttleModel> PremiumShuttleModel::clone() const { return make_unique<PremiumShuttleModel>(); }
