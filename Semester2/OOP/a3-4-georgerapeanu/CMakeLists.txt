cmake_minimum_required(VERSION 3.21)
project(a3_4_georgerapeanu C)

set(CMAKE_C_STANDARD 11)

add_executable(a3_4_georgerapeanu
        src/domain/country.c
        src/domain/vector.c
        src/domain/errors.c
        src/repository/repository.c
        src/controller/country_controller.c
        src/utils/utils.c
        src/ui/ui.c
        app/main.c
        src/domain/operation.c
        src/domain/undo_redo_operation.c
        src/controller/undo_redo_controller.c
        src/repository/undo_redo_repository.c
        )


add_executable(a3_4_georgerapeanu_tests
        src/domain/country.c
        src/domain/vector.c
        src/domain/errors.c
        src/utils/utils.c
        src/repository/repository.c
        src/controller/country_controller.c
        src/domain/operation.c
        src/domain/undo_redo_operation.c
        src/controller/undo_redo_controller.c
        src/repository/undo_redo_repository.c
        tests/src/domain/country_tests.c
        tests/src/domain/errors_tests.c
        tests/src/domain/vector_tests.c
        tests/src/domain/domain_tests.c
        tests/app/main.c
        tests/src/utils/utils_tests.c
        tests/src/repository/repository_tests.c
        tests/src/controller/country_controller_tests.c
        tests/src/domain/operation_tests.c
        tests/src/domain/undo_redo_operation_tests.c
        tests/src/controller/undo_redo_tests.c)