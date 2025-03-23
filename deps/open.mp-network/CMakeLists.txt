include(FetchContent)
FetchContent_Declare(
  open.mp-network
  GIT_REPOSITORY https://github.com/openmultiplayer/open.mp-network.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(open.mp-network)
