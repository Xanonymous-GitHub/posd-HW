#include "../../src/utils/file_reader.h"

TEST(FileReaderTest, ReadShouldBeCorrect) {
    const FileReader reader("test/utils/test_input.txt");
    const auto result = reader.read();
    ASSERT_EQ(
        "CompoundShape (\n    CompoundShape (\n        Circle (\n            Vector ((0.00, 0.00), (0.00, 5.00))\n        ), Rectangle (\n            Vector ((0.00, 0.00), (0.00, 5.00)),\n            Vector ((0.00, 0.00), (5.00, 0.00))\n        )\n    ), CompoundShape (\n        Circle (\n            Vector ((0.00, 0.00), (0.00, 3.00))\n        )\n    )\n)",
        result);
}
