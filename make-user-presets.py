#!/usr/bin/env python
import sys
import json
from argparse import ArgumentParser
from pathlib import Path


def main(args):
    config = process_command_line(args)
    return run(config)


def process_command_line(args):
    parser = make_command_line_parser(args[0])
    config = parser.parse_args(args[1:])
    validate_input(config)
    return config


def make_command_line_parser(prog):
    parser = ArgumentParser(prog=prog)
    parser.add_argument("filename", type=Path)
    parser.add_argument(
        "--output-file", "-o", type=Path, default=Path("CMakeUserPresets.json")
    )
    parser.add_argument(
        "--stdout",
        action="store_true",
        default=False,
        help="Dump the user presets to stdout instead of a file",
    )
    parser.add_argument(
        "--shared-build-directory",
        action="store_true",
        default=False,
        help="All presets share the same build directory",
    )

    parser.add_argument(
        "--shared-devel-build-directory",
        action="store_true",
        default=False,
        help="Normal and `devel` builds share the same directory ",
    )

    parser.add_argument(
        "--replace-existing",
        action="store_true",
        default=False,
        help="""Overwrite the output file if it exists.
        Otherwise, it is an error if the output file
        already exists""",
    )
    return parser


def validate_input(config):
    if not config.filename.exists():
        raise RuntimeError(MISSING_INPUT_ERROR.format(input_file=config.filename))
    if (
        config.output_file.exists()
        and not config.replace_existing
        and not config.stdout
    ):
        raise RuntimeError(EXISTING_OUTPUT_ERROR.format(output_file=config.output_file))


def run(config):
    with open(config.filename, "r", encoding="utf-8") as inp:
        input_data = json.load(inp)
    output_data = {
        "version": 6,
        "cmakeMinimumRequired": {"major": 3, "minor": 21, "patch": 0},
        "configurePresets": [
            make_configure_preset(config, compiler) for compiler in input_data
        ]
        + [make_devel_configure_preset(config, compiler) for compiler in input_data],
        "buildPresets": (
            [{"name": "baseBuild", "jobs": 16, "configurePreset": "default"}]
            + [make_build_preset(compiler["name"]) for compiler in input_data]
            + [
                make_build_preset(compiler["name"] + "-devel")
                for compiler in input_data
            ]
        ),
        "testPresets": (
            [
                {
                    "name": "baseTest",
                    "output": {"outputOnFailure": True},
                    "configurePreset": "default",
                    "execution": {"jobs": 16},
                }
            ]
            + [make_test_preset(compiler["name"]) for compiler in input_data]
            + [make_test_preset(compiler["name"] + "-devel") for compiler in input_data]
        ),
        "workflowPresets": [
            make_workflow_preset(compiler["name"]) for compiler in input_data
        ]
        + [
            make_workflow_preset(compiler["name"] + "-devel") for compiler in input_data
        ],
    }
    if config.stdout:
        print(json.dumps(output_data))
    else:
        with open(config.output_file, "w", encoding="utf-8") as out:
            json.dump(output_data, out, indent=4)


def make_configure_preset(config, compiler):
    return {
        "name": compiler["name"],
        "inherits": "default",
        "hidden": False,
        "binaryDir": binary_directory(config, compiler),
        "cacheVariables": {"CMAKE_BUILD_TYPE": "Release"},
        "environment": {
            "COMPILER_ROOT": compiler["root"],
            "PATH": "$env{COMPILER_ROOT}/bin:$penv{PATH}",
            "LIBRARY_PATH": "$env{COMPILER_ROOT}/lib:$env{COMPILER_ROOT}/lib64:$penv{LIBRARY_PATH}",
            "LD_LIBRARY_PATH": "$env{COMPILER_ROOT}/lib:$env{COMPILER_ROOT}/lib64:$penv{LD_LIBRARY_PATH}",
            "CPATH": "$env{COMPILER_ROOT}/lib",
            "CC": "$env{COMPILER_ROOT}/bin/" + compiler["cc"],
            "CXX": "$env{COMPILER_ROOT}/bin/" + compiler["cxx"],
        },
    }


def make_devel_configure_preset(config, compiler):
    return {
        "name": compiler["name"] + "-devel",
        "inherits": compiler["name"],
        "hidden": False,
        "binaryDir": devel_binary_directory(config, compiler),
        "cacheVariables": {
            "CMAKE_BUILD_TYPE": "RelWithDebInfo",
        },
    }


def devel_binary_directory(config, compiler):
    return (
        binary_directory(config, compiler) + "-devel"
        if not config.shared_devel_build_directory
        else ""
    )


def binary_directory(config, compiler):
    return "${sourceDir}/build" + (
        "-" + compiler["name"] if not config.shared_build_directory else ""
    )


def make_build_preset(workflow_name):
    return {
        "name": workflow_name,
        "inherits": "baseBuild",
        "configurePreset": workflow_name,
    }


def make_test_preset(workflow_name):
    return {
        "name": workflow_name,
        "inherits": "baseTest",
        "configurePreset": workflow_name,
    }


def make_workflow_preset(workflow_name):
    return {
        "name": workflow_name,
        "steps": [
            {"type": "configure", "name": workflow_name},
            {"type": "build", "name": workflow_name},
            {"type": "test", "name": workflow_name},
        ],
    }


MISSING_INPUT_ERROR = """
Could not find input file: {input_file}
"""

EXISTING_OUTPUT_ERROR = """
The output file ({output_file}) already exists.  To
overwrite it, provide the switch --replace-existing.
"""

if __name__ == "__main__":
    sys.exit(main(sys.argv))
