#include <gtest/gtest.h>
#include <stdint.h>
#include <string.h>
#include "fcc_sonar.h"
#include "fcc_pos.h"
#include "sim_lib.h"
#include "fc_lib.h"
#include "fclink.h"

TEST(sim_lib, init)
{
    fcc_sonar_t sonar, sonar2;
    init_sim_lib();
    init_fc_lib();

    sonar.dist = 375;
    sim_lib_send(eSonar, &sonar);
    sleep(1);
    EXPECT_TRUE(sim_get_data(eSonar, &sonar2));
    EXPECT_EQ(sonar.dist, sonar2.dist);
    while(1)
    sleep(1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}