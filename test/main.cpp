#include <gtest/gtest.h>
#include <stdint.h>
#include <string.h>
#include "fcl_sim_proxy.h"
#include "fcl_fc_proxy.h"
#include <pthread.h>

TEST(sim_lib, init)
{
    fcl_sonar_t sonar, sonar2;
    fcl_init_fc_proxy();
    fcl_init_sim_proxy();

    sonar.dist = 375;
    fcl_send_to_fc(eSonar, &sonar);
    pthread_yield();
    sleep(1);
    EXPECT_TRUE(fcl_get_from_sim(eSonar, &sonar2));
    EXPECT_EQ(sonar.dist, sonar2.dist);
    EXPECT_EQ(sonar.dist, sonar2.dist);

    sonar.dist = 212;
    fcl_send_to_fc(eSonar, &sonar);
    pthread_yield();
    sleep(1);
    EXPECT_TRUE(fcl_get_from_sim(eSonar, &sonar2));
    EXPECT_EQ(sonar.dist, sonar2.dist);

    fcl_deinit_fc_proxy();
    fcl_deinit_sim_proxy();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}