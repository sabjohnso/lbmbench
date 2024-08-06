# This script is intended to help deal with differences in the
# formatting between versions of clang-format. The correct
# version of clang-format is 14.0, which is the latest on
# unbuntu-latest.  When that version is updated, the expected
# version should be updated.

# The PATH is altered here to put the default version of
# clang-format ahead of other version that may be in the path
# from building the code.

expected_clang_format_version="14.0"

export PATH=/usr/bin:$PATH

if [[ "$(clang-format --version)" != *"$expected_clang_format_version"* ]]
then
    echo "Error: clang-format version mismatch"
    echo "formatting may not be correct"
    echo "expected: $expected_clang_format_version"
    echo "actual: $(clang-format --version)"
    exit 1
fi
