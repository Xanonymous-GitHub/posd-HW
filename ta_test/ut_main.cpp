#include <gtest/gtest.h>
#include "./ut_point.h"
#include "./ut_two_dimensional_vector.h"
#include "./ut_triangle.h"
#include "./ut_rectangle.h"
#include "./ut_circle.h"
#include "./ut_shape.h"
#include "./ut_compound_shape.h"
#include "./iterator/ut_null_iterator.h"
#include "./iterator/ut_list_compound_iterator.h"
#include "./iterator/ut_dfs_compound_iterator.h"
#include "./iterator/ut_bfs_compound_iterator.h"
#include "./ut_bounding_box.h"
#include "./visitor/ut_collision_detector.h"
#include "./builder/ut_shape_builder.h"
#include "./builder/ut_scanner.h"
#include "./builder/ut_shape_parser.h"
#include "./utils/ut_file_reader.h"
#include "./graphics/ut_sdl_adapter.h"
#include "./graphics/mock_sdl_renderer.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}