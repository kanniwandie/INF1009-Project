/**
 * @file ShuttleModel.h
 * @brief Defines the shuttle model hierarchy used for capacity and display behaviour.
 * @author Chen Xiyuan
 */
#ifndef SHUTTLE_MODEL_H
#define SHUTTLE_MODEL_H

#include <memory>
#include <string>
using namespace std;

/**
 * @brief Abstract base class for shuttle capacity models.
 * @author Chen Xiyuan
 */
class ShuttleModel {
public:
    virtual ~ShuttleModel() = default;
    virtual int getMaxSeats() const = 0;
    virtual string getName() const = 0;
    // The exact token used in the Small/Family/Premium data file format and
    // expected back by ShuttleParser - distinct from getName(), which is a
    // human-readable label for console/report display (e.g. "Small Shuttle").
    virtual string getCode() const = 0;
    virtual unique_ptr<ShuttleModel> clone() const = 0;
};

/**
 * @brief Small-capacity shuttle model used for minimal dispatch scenarios.
 * @author Chen Xiyuan
 */
class SmallShuttleModel : public ShuttleModel {
public:
    int getMaxSeats() const override;
    string getName() const override;
    string getCode() const override;
    unique_ptr<ShuttleModel> clone() const override;
};

/**
 * @brief Family-capacity shuttle model used for larger passenger groups.
 * @author Chen Xiyuan
 */
class FamilyShuttleModel : public ShuttleModel {
public:
    int getMaxSeats() const override;
    string getName() const override;
    string getCode() const override;
    unique_ptr<ShuttleModel> clone() const override;
};

/**
 * @brief Premium-capacity shuttle model used for high-capacity dispatches.
 * @author Chen Xiyuan
 */
class PremiumShuttleModel : public ShuttleModel {
public:
    int getMaxSeats() const override;
    string getName() const override;
    string getCode() const override;
    unique_ptr<ShuttleModel> clone() const override;
};

#endif
