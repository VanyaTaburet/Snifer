# ���������� � ������-�������
add_library(sniffer_lib
  sniffer.cpp
)

target_include_directories(sniffer_lib
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

# ����������� ����
add_executable(sniffer
  main.cpp
)

target_link_libraries(sniffer
  PRIVATE sniffer_lib
)
