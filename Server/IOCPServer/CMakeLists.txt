cmake_minimum_required(VERSION 3.16)
project(IOCPServer VERSION 1.0.0 LANGUAGES CXX)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 컴파일러별 최적화 플래그
if(MSVC)
    # Visual Studio 컴파일러 옵션
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Ob2 /MD /DNDEBUG")
    
    # 메모리 누수 검사 (디버그 모드)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_CRTDBG_MAP_ALLOC")
    
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC 컴파일러 옵션
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

# 소스 파일 목록
set(SOURCES
    src/main.cpp
    src/IOCPServer.cpp
    src/NetworkManager.cpp
    src/NetworkSessionManager.cpp
    src/ClientManager.cpp
    src/ClientSession.cpp
    src/GameUpdater.cpp
    src/PacketDispatcher.cpp
    src/Logger.cpp
)

# 헤더 파일 목록
set(HEADERS
    include/IOCPServer.h
    include/NetworkManager.h
    include/NetworkSessionManager.h
    include/ClientManager.h
    include/ClientSession.h
    include/GameUpdater.h
    include/PacketDispatcher.h
    include/PacketTypes.h
    include/Logger.h
)

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 인클루드 디렉토리 설정
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Windows 전용 라이브러리 링크
if(WIN32)
    target_link_libraries(${PROJECT_NAME} 
        ws2_32      # Windows Sockets 2
        mswsock     # Microsoft Winsock
        kernel32    # Windows Kernel
        user32      # Windows User
        advapi32    # Windows Advanced API
    )
    
    # Windows 매크로 정의
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        WIN32_LEAN_AND_MEAN     # Windows 헤더 크기 최소화
        NOMINMAX                # min/max 매크로 비활성화
        _WIN32_WINNT=0x0601     # Windows 7 이상 지원
        WINVER=0x0601           # Windows 버전
    )
endif()

# 빌드 타입별 정의
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:RelWithDebInfo>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    $<$<CONFIG:MinSizeRel>:NDEBUG>
)

# 출력 디렉토리 설정
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
)

# 추가 컴파일 옵션 (성능 최적화)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(MSVC)
        # MSVC 최적화 옵션
        target_compile_options(${PROJECT_NAME} PRIVATE 
            /fp:fast        # 빠른 부동소수점 연산
            /Gy             # 함수 수준 링킹
            /GL             # 전체 프로그램 최적화
        )
        target_link_options(${PROJECT_NAME} PRIVATE
            /LTCG           # 링크 타임 코드 생성
            /OPT:REF        # 참조되지 않는 함수/데이터 제거
            /OPT:ICF        # 동일한 COMDAT 병합
        )
    endif()
endif()

# 정적 분석 도구 (선택사항)
if(ENABLE_STATIC_ANALYSIS AND MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_EnableClangTidyCodeAnalysis true
        VS_GLOBAL_ClangTidyChecks "-*,readability-*,performance-*,modernize-*"
    )
endif()

# 유닛 테스트 (선택사항)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# 설치 규칙
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# 설정 파일 복사
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/config)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/config/
        DESTINATION config
        FILES_MATCHING PATTERN "*.ini" PATTERN "*.json" PATTERN "*.xml"
    )
endif()

# 패키징 정보
set(CPACK_PACKAGE_NAME "IOCPServer")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "IOCP Based Multiplayer Game Server")
set(CPACK_PACKAGE_VENDOR "Game Development Team")

include(CPack)

# 빌드 정보 출력
message(STATUS "========================================")
message(STATUS "프로젝트: ${PROJECT_NAME}")
message(STATUS "버전: ${PROJECT_VERSION}")
message(STATUS "빌드 타입: ${CMAKE_BUILD_TYPE}")
message(STATUS "컴파일러: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ 표준: ${CMAKE_CXX_STANDARD}")
message(STATUS "출력 디렉토리: ${CMAKE_BINARY_DIR}/bin")
message(STATUS "========================================")