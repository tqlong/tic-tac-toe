set(sources
    src/game_state.cpp
    src/alpha_beta.cpp
    src/controller.cpp
    src/render_engine.cpp
    src/resource_manager.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/tictactoe/game_state.h
    include/tictactoe/controller.h
    include/tictactoe/render_engine.h
    include/tictactoe/resource_manager.h
)

set(test_sources
  src/game_state_test.cpp
)
