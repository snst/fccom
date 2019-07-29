#include <gtest/gtest.h>
#include <stdint.h>
#include <string.h>
#include "fcl_sim_proxy.h"
#include "fcl_fc_proxy.h"
#include <pthread.h>
#include <unistd.h>

#define SOCKET_SLEEP (5u)

void sleep_ms(uint32_t milliseconds)
{
    usleep(milliseconds * 1000u);
}

static fclCmd_t last_data;

void data_callback(void *ptr, fclCmd_t data)
{
    last_data = data;
}

class sim_lib : public ::testing::Test
{
public:
    sim_lib()
    {
    }

    void SetUp() override
    {
        last_data = eLastCmd;
        fcl_init_fc_proxy(NULL, NULL);
        fcl_init_sim_proxy(&data_callback);
    }

    void TearDown() override
    {
        fcl_deinit_fc_proxy();
        fcl_deinit_sim_proxy();
    }
};

TEST_F(sim_lib, ut_sonar)
{
    fcl_sonar_t sonar, sonar2;

    sonar.dist = 375;
    fcl_send_to_fc(eSonar, &sonar);
    sleep_ms(SOCKET_SLEEP);
    EXPECT_TRUE(fcl_get_from_sim(eSonar, &sonar2));
    EXPECT_EQ(sonar.dist, sonar2.dist);
    EXPECT_EQ(sonar.dist, sonar2.dist);

    sonar.dist = 212;
    fcl_send_to_fc(eSonar, &sonar);
    sleep_ms(SOCKET_SLEEP);
    EXPECT_TRUE(fcl_get_from_sim(eSonar, &sonar2));
    EXPECT_EQ(sonar.dist, sonar2.dist);
}

TEST_F(sim_lib, ut_pos)
{
    fcl_pos_t pos, pos2;
    pos.x = 33;
    pos.z = 27;
    fcl_send_to_fc(ePos, &pos);
    sleep_ms(SOCKET_SLEEP);
    EXPECT_TRUE(fcl_get_from_sim(ePos, &pos2));
    EXPECT_EQ(pos.x, pos2.x);
    EXPECT_EQ(pos.y, pos2.y);
}

TEST_F(sim_lib, ut_gps)
{
    fcl_gps_t gps, gps2;
    gps.latitude = 66.12;
    fcl_send_to_fc(eGps, &gps);
    sleep_ms(SOCKET_SLEEP);
    EXPECT_TRUE(fcl_get_from_sim(eGps, &gps2));
    EXPECT_EQ(gps.latitude, gps2.latitude);
    EXPECT_EQ(eGps, last_data);
}

TEST_F(sim_lib, ut_imu)
{
    fcl_imu_t imu, imu2;
    imu.orientation_quat_w = 77.32;
    fcl_send_to_fc(eImu, &imu);
    sleep_ms(SOCKET_SLEEP);
    EXPECT_TRUE(fcl_get_from_sim(eImu, &imu2));
    EXPECT_EQ(imu.orientation_quat_w, imu2.orientation_quat_w);
}

TEST_F(sim_lib, ut_motor)
{
    fcl_motor_t motor, motor2;
    motor.motor[0] = 332.1f;
    motor.motor[1] = 392.3f;
    motor.motor[2] = 2.4f;
    motor.motor[3] = 112.7f;
    
    fcl_send_to_sim(eMotor, &motor);
    sleep_ms(SOCKET_SLEEP);
    EXPECT_TRUE(fcl_get_from_fc(eMotor, &motor2));
    EXPECT_EQ(motor.motor[0], motor2.motor[0]);
    EXPECT_EQ(motor.motor[1], motor2.motor[1]);
    EXPECT_EQ(motor.motor[2], motor2.motor[2]);
    EXPECT_EQ(motor.motor[3], motor2.motor[3]);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}