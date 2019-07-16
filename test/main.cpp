#include <gtest/gtest.h>
#include <stdint.h>
#include <string.h>
#include "fcl_sim_proxy.h"
#include "fcl_fc_proxy.h"
#include <pthread.h>
#include <unistd.h>

void sleep_ms(uint32_t milliseconds)
{
    usleep(milliseconds * 1000u);
}

class sim_lib : public ::testing::Test
{
public:
    sim_lib()
    {
    }

    void SetUp() override
    {
        fcl_init_fc_proxy();
        fcl_init_sim_proxy();
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
    sleep_ms(100);
    EXPECT_TRUE(fcl_get_from_sim(eSonar, &sonar2));
    EXPECT_EQ(sonar.dist, sonar2.dist);
    EXPECT_EQ(sonar.dist, sonar2.dist);

    sonar.dist = 212;
    fcl_send_to_fc(eSonar, &sonar);
    sleep_ms(100);
    EXPECT_TRUE(fcl_get_from_sim(eSonar, &sonar2));
    EXPECT_EQ(sonar.dist, sonar2.dist);
}

TEST_F(sim_lib, ut_pos)
{
    fcl_pos_t pos, pos2;
    pos.x = 33;
    pos.z = 27;
    fcl_send_to_fc(ePos, &pos);
    sleep_ms(100);
    EXPECT_TRUE(fcl_get_from_sim(ePos, &pos2));
    EXPECT_EQ(pos.x, pos2.x);
    EXPECT_EQ(pos.y, pos2.y);
}

TEST_F(sim_lib, ut_gps)
{
    fcl_gps_t gps, gps2;
    gps.latitude = 66.12;
    fcl_send_to_fc(eGps, &gps);
    sleep_ms(100);
    EXPECT_TRUE(fcl_get_from_sim(eGps, &gps2));
    EXPECT_EQ(gps.latitude, gps2.latitude);
}

TEST_F(sim_lib, ut_imu)
{
    fcl_imu_t imu, imu2;
    imu.orientation_quat_w = 77.32;
    fcl_send_to_fc(eImu, &imu);
    sleep_ms(100);
    EXPECT_TRUE(fcl_get_from_sim(eImu, &imu2));
    EXPECT_EQ(imu.orientation_quat_w, imu2.orientation_quat_w);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}