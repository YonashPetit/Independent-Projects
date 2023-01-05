import pygame, sys
from sudoku_generator import *
from constants import *
# main menu
def draw_game_start(screen):
    # initialize title font
    start_title_font = pygame.font.Font(None, 80)
    subtitle_font = pygame.font.Font(None, 70)
    button_font = pygame.font.Font(None, 40)

    # Color background
    screen.fill(BG_COLOR)

    # Initialize and draw welcome to sudoku
    title_surface = start_title_font.render("Welcome to Sudoku", 0, LINE_COLOR)
    title_rectangle = title_surface.get_rect(
        center=(WIDTH // 2 - 30, HEIGHT // 2 - 200))
    screen.blit(title_surface, title_rectangle)

    # Initialize and draw Select Game Mode
    subtitle_surface = subtitle_font.render("Select Game Mode:", 0, LINE_COLOR)
    subtitle_rectangle = subtitle_surface.get_rect(
        center=(WIDTH // 2, HEIGHT // 2))
    screen.blit(subtitle_surface, subtitle_rectangle)

    # Initialize buttons
    # Initialize text first
    easy_text = button_font.render("Easy", 0, (255, 255, 255))
    medium_text = button_font.render("Medium", 0, (255, 255, 255))
    hard_text = button_font.render("Hard", 0, (255, 255, 255))

    # Initialize button background color and text
    easy_surface = pygame.Surface((easy_text.get_size()[0] + 20, easy_text.get_size()[1] + 20))
    easy_surface.fill(LINE_COLOR)
    easy_surface.blit(easy_text, (10, 10))
    medium_surface = pygame.Surface((medium_text.get_size()[0] + 20, medium_text.get_size()[1] + 20))
    medium_surface.fill(LINE_COLOR)
    medium_surface.blit(medium_text, (10, 10))
    hard_surface = pygame.Surface((hard_text.get_size()[0] + 20, hard_text.get_size()[1] + 20))
    hard_surface.fill(LINE_COLOR)
    hard_surface.blit(hard_text, (10, 10))

    # Initialize button rectangle
    easy_rectangle = easy_surface.get_rect(
        center=(WIDTH // 2 - 200, HEIGHT // 2 + 150))
    medium_rectangle = medium_surface.get_rect(
        center=(WIDTH // 2, HEIGHT // 2 + 150))
    hard_rectangle = hard_surface.get_rect(
        center=(WIDTH // 2 + 200, HEIGHT // 2 + 150))

    # Draw buttons
    screen.blit(easy_surface, easy_rectangle)
    screen.blit(medium_surface, medium_rectangle)
    screen.blit(hard_surface, hard_rectangle)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                # checks if mouse is on easy button
                if easy_rectangle.collidepoint(event.pos):
                    return 1 # if the mouse is on the easy button, we can return to main
                elif medium_rectangle.collidepoint(event.pos):
                    return 2
                elif hard_rectangle.collidepoint(event.pos):
                    return 3
        pygame.display.update()

def draw_game_over(screen, winner_loser):
    game_over_font = pygame.font.Font(None, 100)
    game_won_font = pygame.font.Font(None, 100)
    button_font = pygame.font.Font(None, 40)
    screen.fill(BG_COLOR)
    if winner_loser: # game won screen
        game_won_surface = game_won_font.render("Game Won!", 0, (0, 0, 0))
        game_won_rectangle = game_won_surface.get_rect(
            center=(WIDTH // 2, HEIGHT // 2 - 200))
        screen.blit(game_won_surface, game_won_rectangle)
        exit_text = button_font.render("EXIT", 0, (255, 255, 255))
        exit_surface = pygame.Surface((exit_text.get_size()[0] + 20, exit_text.get_size()[1] + 20))
        exit_surface.fill(LINE_COLOR)
        exit_surface.blit(exit_text, (10, 10))
        exit_rectangle = exit_surface.get_rect(
            center=(WIDTH // 2, HEIGHT // 2 + 150))
        screen.blit(exit_surface, exit_rectangle)
    else: # game over screen
        game_over_surface = game_over_font.render("Game Over :(", 0, (0, 0, 0))
        game_over_rectangle = game_over_surface.get_rect(
            center=(WIDTH // 2, HEIGHT // 2 - 200))
        screen.blit(game_over_surface, game_over_rectangle)
        restart_text = button_font.render("RESTART", 0, (255, 255, 255))
        restart_surface = pygame.Surface((restart_text.get_size()[0] + 20, restart_text.get_size()[1] + 20))
        restart_surface.fill(LINE_COLOR)
        restart_surface.blit(restart_text, (10, 10))
        restart_rectangle = restart_surface.get_rect(
            center=(WIDTH // 2, HEIGHT // 2 + 150))
        screen.blit(restart_surface, restart_rectangle)
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if winner_loser:
                    if exit_rectangle.collidepoint(event.pos):
                        sys.exit()
                if restart_rectangle.collidepoint(event.pos):
                    return 4
        pygame.display.update()

#makes the red ring around the cell you choose
def select(x, y):
    if y <= 630:
        xstart = x // 70 * 70
        ystart = y // 70 * 70
        xend = xstart + 70
        yend = ystart + 70

        pygame.draw.line(
            screen,
            RED,
            (xstart, ystart),
            (xend, ystart),
            HIGHLIGHT_WIDTH
        )

        pygame.draw.line(
            screen,
            RED,
            (xstart, yend),
            (xend, yend),
            HIGHLIGHT_WIDTH
        )

        pygame.draw.line(
            screen,
            RED,
            (xstart, ystart),
            (xstart, yend),
            HIGHLIGHT_WIDTH
        )

        pygame.draw.line(
            screen,
            RED,
            (xend, ystart),
            (xend, yend),
            HIGHLIGHT_WIDTH
        )

#draws the grid (also delets)
def draw_grid():
    #Horizontal Skinny Lines
    for i in range(10):
        pygame.draw.line(
            screen,
            BOARD_LINE_COLOR,
            (0, SQUARE_SIZE * i ),
            (WIDTH, SQUARE_SIZE * i),
            BOARD_LINE_ROWS
        )
        if i == 3 or i == 6:
            pygame.draw.line(
                screen,
                BOARD_LINE_COLOR,
                (0, SQUARE_SIZE * i),
                (WIDTH, SQUARE_SIZE * i),
                BOARD_LINE_WIDTH-2
            )

    #Verticle Skinny Lines
    for i in range(9):
        pygame.draw.line(
            screen,
            BOARD_LINE_COLOR,
            (SQUARE_SIZE * i , 0),
            (SQUARE_SIZE * i, HEIGHT-SQUARE_SIZE),
            BOARD_LINE_COLS
        )

        if i == 3 or i == 6:
            pygame.draw.line(
                screen,
                BOARD_LINE_COLOR,
                (SQUARE_SIZE * i, 0),
                (SQUARE_SIZE * i, HEIGHT - SQUARE_SIZE),
                BOARD_LINE_WIDTH-2
            )

#this part draws the inital chips
def draw_chips():
    #draw a text, 1. define a surface, 2. define the location
    chip_0_surface = chip_font.render("0", 0, BG_COLOR)
    chip_1_surface = chip_font.render("1", 1, NUMBER_COLOR)
    chip_2_surface = chip_font.render("2", 1, NUMBER_COLOR)
    chip_3_surface = chip_font.render("3", 1, NUMBER_COLOR)
    chip_4_surface = chip_font.render("4", 1, NUMBER_COLOR)
    chip_5_surface = chip_font.render("5", 1, NUMBER_COLOR)
    chip_6_surface = chip_font.render("6", 1, NUMBER_COLOR)
    chip_7_surface = chip_font.render("7", 1, NUMBER_COLOR)
    chip_8_surface = chip_font.render("8", 1, NUMBER_COLOR)
    chip_9_surface = chip_font.render("9", 1, NUMBER_COLOR)

    for row in range(BOARD_ROWS):
        for col in range(BOARD_COLS):
            if reset[row][col] == 0:
                pygame.draw.rect(screen, BG_COLOR, [(SQUARE_SIZE * col + SQUARE_SIZE // 2)-31, (SQUARE_SIZE * row + SQUARE_SIZE // 2)-31, 60, 60])
            elif reset[row][col] == 1:
                chip_1_rect = chip_1_surface.get_rect(center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                screen.blit(chip_1_surface, chip_1_rect)
            elif reset[row][col] == 2:
                chip_2_rect = chip_2_surface.get_rect(center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                screen.blit(chip_2_surface, chip_2_rect)
            elif reset[row][col] == 3:
                chip_3_rect = chip_3_surface.get_rect(center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                screen.blit(chip_3_surface, chip_3_rect)
            elif reset[row][col] == 4:
                chip_4_rect = chip_4_surface.get_rect(center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                screen.blit(chip_4_surface, chip_4_rect)
            elif reset[row][col] == 5:
                chip_5_rect = chip_5_surface.get_rect(center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                screen.blit(chip_5_surface, chip_5_rect)
            elif reset[row][col] == 6:
                chip_6_rect = chip_6_surface.get_rect(center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                screen.blit(chip_6_surface, chip_6_rect)
            elif reset[row][col] == 7:
                chip_7_rect = chip_7_surface.get_rect(center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                screen.blit(chip_7_surface, chip_7_rect)
            elif reset[row][col] == 8:
                chip_8_rect = chip_8_surface.get_rect(center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                screen.blit(chip_8_surface, chip_8_rect)
            elif reset[row][col] == 9:
                chip_9_rect = chip_9_surface.get_rect(center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                screen.blit(chip_9_surface, chip_9_rect)

 #this part deletes what was previously in a cell
def blank(x, y):
    xstart = (x // 70 * 70)+5
    ystart = (y // 70 * 70)+5
    pygame.draw.rect(screen, BG_COLOR, [xstart,ystart,60,60])

#this part produces a sketch of what the user inputs
def sketch(value, row, col):
    chip_variable_surface = sketch_chip_font.render(f"{value}", 1, (150,150,150))
    chip_variable_rect = chip_variable_surface.get_rect(center=((SQUARE_SIZE * col + SQUARE_SIZE // 2)-15, (SQUARE_SIZE * row + SQUARE_SIZE // 2)-10))
    screen.blit(chip_variable_surface, chip_variable_rect)

#this part finalizes a sketch after the user hits enter
def keep(value, row, col):
    chip_variable_surface = sketch_chip_font.render(f"{value}", 1, (0,0,0))
    chip_variable_rect = chip_variable_surface.get_rect(center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
    screen.blit(chip_variable_surface, chip_variable_rect)

#this converts the user's key press into a sketch on the board
def keypress():
    if event.type == pygame.KEYDOWN:
        if event.key == pygame.K_1 :
            board[row][col] = 1
            return board
        if event.key == pygame.K_2:
            board[row][col] = 2
            return board
        if event.key == pygame.K_3:
            board[row][col] = 3
            return board
        if event.key == pygame.K_4:
            board[row][col] = 4
            return board
        if event.key == pygame.K_5:
            board[row][col] = 5
            return board
        if event.key == pygame.K_6:
            board[row][col] = 6
            return board
        if event.key == pygame.K_7:
            board[row][col] = 7
            return board
        if event.key == pygame.K_8:
            board[row][col] = 8
            return board
        if event.key == pygame.K_9 :
            board[row][col] = 9
            return board

def buttons():
    button_font = pygame.font.Font(None, 40)
    restart_text = button_font.render("RESTART", 0, (255, 255, 255))
    restart_surface = pygame.Surface((restart_text.get_size()[0] + 20, restart_text.get_size()[1] + 20))
    screen.fill(BG_COLOR)
    restart_surface.fill(LINE_COLOR)
    restart_surface.blit(restart_text, (10, 10))
    restart_rectangle = restart_surface.get_rect(
        center=(WIDTH // 2 - 20, HEIGHT // 2 + 320))
    screen.blit(restart_surface, restart_rectangle)
    reset_text = button_font.render("RESET", 0, (255, 255, 255))
    reset_surface = pygame.Surface((reset_text.get_size()[0] + 20, reset_text.get_size()[1] + 20))
    reset_surface.fill(LINE_COLOR)
    reset_surface.blit(reset_text, (10, 10))
    reset_rectangle = reset_surface.get_rect(
        center=(WIDTH // 2 - 200, HEIGHT // 2 + 320))
    screen.blit(reset_surface, reset_rectangle)
    exit_text = button_font.render("EXIT", 0, (255, 255, 255))
    exit_surface = pygame.Surface((exit_text.get_size()[0] + 20, exit_text.get_size()[1] + 20))
    exit_surface.fill(LINE_COLOR)
    exit_surface.blit(exit_text, (10, 10))
    exit_rectangle = exit_surface.get_rect(
        center=(WIDTH // 2 + 150, HEIGHT // 2 + 320))
    screen.blit(exit_surface, exit_rectangle)
    return

# repeat of the code in main body for the button
def main():
    def draw_game_start(screen):
        start_title_font = pygame.font.Font(None, 80)
        subtitle_font = pygame.font.Font(None, 70)
        button_font = pygame.font.Font(None, 40)

        screen.fill(BG_COLOR)
        title_surface = start_title_font.render("Welcome to Sudoku", 0, LINE_COLOR)
        title_rectangle = title_surface.get_rect(
            center=(WIDTH // 2 - 30, HEIGHT // 2 - 200))
        screen.blit(title_surface, title_rectangle)

        subtitle_surface = subtitle_font.render("Select Game Mode:", 0, LINE_COLOR)
        subtitle_rectangle = subtitle_surface.get_rect(
            center=(WIDTH // 2, HEIGHT // 2))
        screen.blit(subtitle_surface, subtitle_rectangle)

        easy_text = button_font.render("Easy", 0, (255, 255, 255))
        medium_text = button_font.render("Medium", 0, (255, 255, 255))
        hard_text = button_font.render("Hard", 0, (255, 255, 255))

        easy_surface = pygame.Surface((easy_text.get_size()[0] + 20, easy_text.get_size()[1] + 20))
        easy_surface.fill(LINE_COLOR)
        easy_surface.blit(easy_text, (10, 10))
        medium_surface = pygame.Surface((medium_text.get_size()[0] + 20, medium_text.get_size()[1] + 20))
        medium_surface.fill(LINE_COLOR)
        medium_surface.blit(medium_text, (10, 10))
        hard_surface = pygame.Surface((hard_text.get_size()[0] + 20, hard_text.get_size()[1] + 20))
        hard_surface.fill(LINE_COLOR)
        hard_surface.blit(hard_text, (10, 10))

        easy_rectangle = easy_surface.get_rect(
            center=(WIDTH // 2 - 200, HEIGHT // 2 + 150))
        medium_rectangle = medium_surface.get_rect(
            center=(WIDTH // 2, HEIGHT // 2 + 150))
        hard_rectangle = hard_surface.get_rect(
            center=(WIDTH // 2 + 200, HEIGHT // 2 + 150))

        screen.blit(easy_surface, easy_rectangle)
        screen.blit(medium_surface, medium_rectangle)
        screen.blit(hard_surface, hard_rectangle)

        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if easy_rectangle.collidepoint(event.pos):
                        return 1  # if the mouse is on the easy button, we can return to main
                    elif medium_rectangle.collidepoint(event.pos):
                        return 2
                    elif hard_rectangle.collidepoint(event.pos):
                        return 3
            pygame.display.update()

    def draw_game_over(screen, winner_loser):
        game_over_font = pygame.font.Font(None, 100)
        game_won_font = pygame.font.Font(None, 100)
        button_font = pygame.font.Font(None, 40)
        screen.fill(BG_COLOR)
        if winner_loser:
            game_won_surface = game_won_font.render("Game Won!", 0, (0, 0, 0))
            game_won_rectangle = game_won_surface.get_rect(
                center=(WIDTH // 2, HEIGHT // 2 - 200))
            screen.blit(game_won_surface, game_won_rectangle)
            exit_text = button_font.render("EXIT", 0, (255, 255, 255))
            exit_surface = pygame.Surface((exit_text.get_size()[0] + 20, exit_text.get_size()[1] + 20))
            exit_surface.fill(LINE_COLOR)
            exit_surface.blit(exit_text, (10, 10))
            exit_rectangle = exit_surface.get_rect(
                center=(WIDTH // 2, HEIGHT // 2 + 150))
            screen.blit(exit_surface, exit_rectangle)
        else:
            game_over_surface = game_over_font.render("Game Over :(", 0, (0, 0, 0))
            game_over_rectangle = game_over_surface.get_rect(
                center=(WIDTH // 2, HEIGHT // 2 - 200))
            screen.blit(game_over_surface, game_over_rectangle)
            restart_text = button_font.render("RESTART", 0, (255, 255, 255))
            restart_surface = pygame.Surface((restart_text.get_size()[0] + 20, restart_text.get_size()[1] + 20))
            restart_surface.fill(LINE_COLOR)
            restart_surface.blit(restart_text, (10, 10))
            restart_rectangle = restart_surface.get_rect(
                center=(WIDTH // 2, HEIGHT // 2 + 150))
            screen.blit(restart_surface, restart_rectangle)
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if winner_loser:
                        if exit_rectangle.collidepoint(event.pos):
                            sys.exit()
                    if restart_rectangle.collidepoint(event.pos):
                        return 4
            pygame.display.update()

    # makes the red ring around the cell you choose
    def select(x, y):
        if y <= 630:
            xstart = x // 70 * 70
            ystart = y // 70 * 70
            xend = xstart + 70
            yend = ystart + 70

            pygame.draw.line(
                screen,
                RED,
                (xstart, ystart),
                (xend, ystart),
                HIGHLIGHT_WIDTH
            )

            pygame.draw.line(
                screen,
                RED,
                (xstart, yend),
                (xend, yend),
                HIGHLIGHT_WIDTH
            )

            pygame.draw.line(
                screen,
                RED,
                (xstart, ystart),
                (xstart, yend),
                HIGHLIGHT_WIDTH
            )

            pygame.draw.line(
                screen,
                RED,
                (xend, ystart),
                (xend, yend),
                HIGHLIGHT_WIDTH
            )

    # draws the grid (also delets)
    def draw_grid():
        # Horizontal Skinny Lines
        for i in range(10):
            pygame.draw.line(
                screen,
                BOARD_LINE_COLOR,
                (0, SQUARE_SIZE * i),
                (WIDTH, SQUARE_SIZE * i),
                BOARD_LINE_ROWS
            )
            if i == 3 or i == 6:
                pygame.draw.line(
                    screen,
                    BOARD_LINE_COLOR,
                    (0, SQUARE_SIZE * i),
                    (WIDTH, SQUARE_SIZE * i),
                    BOARD_LINE_WIDTH - 2
                )

        # Verticle Skinny Lines
        for i in range(9):
            pygame.draw.line(
                screen,
                BOARD_LINE_COLOR,
                (SQUARE_SIZE * i, 0),
                (SQUARE_SIZE * i, HEIGHT - SQUARE_SIZE),
                BOARD_LINE_COLS
            )

            if i == 3 or i == 6:
                pygame.draw.line(
                    screen,
                    BOARD_LINE_COLOR,
                    (SQUARE_SIZE * i, 0),
                    (SQUARE_SIZE * i, HEIGHT - SQUARE_SIZE),
                    BOARD_LINE_WIDTH - 2
                )

    # this part draws the inital chips
    def draw_chips():
        chip_0_surface = chip_font.render("0", 0, BG_COLOR)
        chip_1_surface = chip_font.render("1", 1, NUMBER_COLOR)
        chip_2_surface = chip_font.render("2", 1, NUMBER_COLOR)
        chip_3_surface = chip_font.render("3", 1, NUMBER_COLOR)
        chip_4_surface = chip_font.render("4", 1, NUMBER_COLOR)
        chip_5_surface = chip_font.render("5", 1, NUMBER_COLOR)
        chip_6_surface = chip_font.render("6", 1, NUMBER_COLOR)
        chip_7_surface = chip_font.render("7", 1, NUMBER_COLOR)
        chip_8_surface = chip_font.render("8", 1, NUMBER_COLOR)
        chip_9_surface = chip_font.render("9", 1, NUMBER_COLOR)

        for row in range(BOARD_ROWS):
            for col in range(BOARD_COLS):
                if reset[row][col] == 0:

                    pygame.draw.rect(screen, BG_COLOR, [(SQUARE_SIZE * col + SQUARE_SIZE // 2) - 31,
                                                        (SQUARE_SIZE * row + SQUARE_SIZE // 2) - 31, 60, 60])
                elif reset[row][col] == 1:
                    chip_1_rect = chip_1_surface.get_rect(
                        center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                    screen.blit(chip_1_surface, chip_1_rect)
                elif reset[row][col] == 2:
                    chip_2_rect = chip_2_surface.get_rect(
                        center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                    screen.blit(chip_2_surface, chip_2_rect)
                elif reset[row][col] == 3:
                    chip_3_rect = chip_3_surface.get_rect(
                        center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                    screen.blit(chip_3_surface, chip_3_rect)
                elif reset[row][col] == 4:
                    chip_4_rect = chip_4_surface.get_rect(
                        center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                    screen.blit(chip_4_surface, chip_4_rect)
                elif reset[row][col] == 5:
                    chip_5_rect = chip_5_surface.get_rect(
                        center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                    screen.blit(chip_5_surface, chip_5_rect)
                elif reset[row][col] == 6:
                    chip_6_rect = chip_6_surface.get_rect(
                        center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                    screen.blit(chip_6_surface, chip_6_rect)
                elif reset[row][col] == 7:
                    chip_7_rect = chip_7_surface.get_rect(
                        center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                    screen.blit(chip_7_surface, chip_7_rect)
                elif reset[row][col] == 8:
                    chip_8_rect = chip_8_surface.get_rect(
                        center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                    screen.blit(chip_8_surface, chip_8_rect)
                elif reset[row][col] == 9:
                    chip_9_rect = chip_9_surface.get_rect(
                        center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
                    screen.blit(chip_9_surface, chip_9_rect)

    # this part deletes what was previously in a cell
    def blank(x, y):
        xstart = (x // 70 * 70) + 5
        ystart = (y // 70 * 70) + 5
        pygame.draw.rect(screen, BG_COLOR, [xstart, ystart, 60, 60])

    # this part produces a sketch of what the user inputs
    def sketch(value, row, col):
        chip_variable_surface = sketch_chip_font.render(f"{value}", 1, (150, 150, 150))
        chip_variable_rect = chip_variable_surface.get_rect(
            center=((SQUARE_SIZE * col + SQUARE_SIZE // 2) - 15, (SQUARE_SIZE * row + SQUARE_SIZE // 2) - 10))
        screen.blit(chip_variable_surface, chip_variable_rect)

    # this part finalizes a sketch after the user hits enter
    def keep(value, row, col):
        chip_variable_surface = sketch_chip_font.render(f"{value}", 1, (0, 0, 0))
        chip_variable_rect = chip_variable_surface.get_rect(
            center=(SQUARE_SIZE * col + SQUARE_SIZE // 2, SQUARE_SIZE * row + SQUARE_SIZE // 2))
        screen.blit(chip_variable_surface, chip_variable_rect)

    def keypress():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_1:
                board[row][col] = 1
                return board
            if event.key == pygame.K_2:
                board[row][col] = 2
                return board
            if event.key == pygame.K_3:
                board[row][col] = 3
                return board
            if event.key == pygame.K_4:
                board[row][col] = 4
                return board
            if event.key == pygame.K_5:
                board[row][col] = 5
                return board
            if event.key == pygame.K_6:
                board[row][col] = 6
                return board
            if event.key == pygame.K_7:
                board[row][col] = 7
                return board
            if event.key == pygame.K_8:
                board[row][col] = 8
                return board
            if event.key == pygame.K_9:
                board[row][col] = 9
                return board

    if __name__ == '__main__':
        while True:
            game_over = False
            winner = 0
            pygame.init()
            screen = pygame.display.set_mode((WIDTH, HEIGHT))
            pygame.display.set_caption("Sudoku")

            draw_game_start(screen)  # calls function to draw start screen
            start_menu_choice = draw_game_start(screen)
            if start_menu_choice == 1:
                create, answer, reset = generate_sudoku(9, 1)
                pygame.display.update()
            if start_menu_choice == 2:
                create, answer, reset = generate_sudoku(9, 40)
                pygame.display.update()
            if start_menu_choice == 3:
                create, answer, reset = generate_sudoku(9, 50)
                pygame.display.update()
            screen.fill(BG_COLOR)

            #these help initialize the board
            board = create
            original_board = []
            for item in create:
                original_board.append(tuple(item))
            pygame.init()
            screen = pygame.display.set_mode((BOARD_WIDTH, HEIGHT))
            chip_font = pygame.font.Font(None, FONT_SIZE)
            sketch_chip_font = pygame.font.Font(None, int(FONT_SIZE - 15))

            #these are the reset, restart, and exit buttons
            buttons()

            # set up initial board:
            draw_grid()
            draw_chips()

            while True:
                # event loop1
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        pygame.quit()
                    if event.type == pygame.MOUSEBUTTONDOWN and not game_over:
                        if exit_rectangle.collidepoint(event.pos):
                            sys.exit()
                        elif restart_rectangle.collidepoint(event.pos):
                            main()
                            continue
                        elif reset_rectangle.collidepoint(event.pos):
                            reset = [list(l) for l in reset]
                            original_board = reset
                            draw_chips()
                        else:
                            x, y = event.pos
                            col = int(x // SQUARE_SIZE)
                            row = int(y // SQUARE_SIZE)
                            draw_grid()
                            select(x, y)

                    # create the sketch:
                    if event.type == pygame.KEYDOWN:
                        if original_board[row][col] == 0:
                            key = keypress()
                            blank(x, y)
                            if board[row][col] != 0:
                                sketch(board[row][col], row, col)

                    # finalize the sketch:
                    if event.type == pygame.KEYDOWN:
                        if original_board[row][col] == 0:
                            if event.key == pygame.K_KP_ENTER:
                                original_board = [list(l) for l in original_board]
                                original_board[row][col] = board[row][col]
                                blank(x, y)
                                keep(board[row][col], row, col)

                # This part is used to decide the winner and loser
                count = 0
                for item in original_board:
                    if 0 in item:
                        count = count + 1
                if count == 0:
                    answer = [list(l) for l in answer]
                    if original_board == answer:
                        # you would transition into the win screen right now
                        winner = True
                        draw_game_over(screen, winner)
                        print("you win")
                        break
                    else:
                        # you would transition into the lose screen right now
                        winner = False
                        draw_game_over(screen, winner)
                        ending = draw_game_over(screen, winner)
                        if ending == 4:
                            main()
                        print("you lose")
                        break
                pygame.display.update()
if __name__ == '__main__':
    while True:
        game_over = False
        winner = 0
        pygame.init()
        screen = pygame.display.set_mode((WIDTH, HEIGHT))
        pygame.display.set_caption("Sudoku")

        draw_game_start(screen)  # calls function to draw start screen
        start_menu_choice = draw_game_start(screen)
        if start_menu_choice == 1:
            create, answer, reset = generate_sudoku(9, 1)
            pygame.display.update()
        if start_menu_choice == 2:
            create, answer, reset = generate_sudoku(9, 40)
            pygame.display.update()
        if start_menu_choice == 3:
            create, answer, reset = generate_sudoku(9, 50)
            pygame.display.update()
        screen.fill(BG_COLOR)

        board = create #these help initialize the board
        original_board = []
        for item in create:
            original_board.append(tuple(item))
        pygame.init()
        screen = pygame.display.set_mode((BOARD_WIDTH, HEIGHT))
        chip_font = pygame.font.Font(None, FONT_SIZE)
        sketch_chip_font = pygame.font.Font(None, int(FONT_SIZE - 15))
        button_font = pygame.font.Font(None, 40)
        restart_text = button_font.render("RESTART", 0, (255, 255, 255))
        restart_surface = pygame.Surface((restart_text.get_size()[0] + 20, restart_text.get_size()[1] + 20))
        screen.fill(BG_COLOR)
        restart_surface.fill(LINE_COLOR)
        restart_surface.blit(restart_text, (10, 10))
        restart_rectangle = restart_surface.get_rect(
            center=(WIDTH // 2 - 20, HEIGHT // 2 + 320))
        screen.blit(restart_surface, restart_rectangle)
        reset_text = button_font.render("RESET", 0, (255, 255, 255))
        reset_surface = pygame.Surface((reset_text.get_size()[0] + 20, reset_text.get_size()[1] + 20))
        reset_surface.fill(LINE_COLOR)
        reset_surface.blit(reset_text, (10, 10))
        reset_rectangle = reset_surface.get_rect(
            center=(WIDTH // 2 - 200, HEIGHT // 2 + 320))
        screen.blit(reset_surface, reset_rectangle)
        exit_text = button_font.render("EXIT", 0, (255, 255, 255))
        exit_surface = pygame.Surface((exit_text.get_size()[0] + 20, exit_text.get_size()[1] + 20))
        exit_surface.fill(LINE_COLOR)
        exit_surface.blit(exit_text, (10, 10))
        exit_rectangle = exit_surface.get_rect(
            center=(WIDTH // 2 + 150, HEIGHT // 2 + 320))
        screen.blit(exit_surface, exit_rectangle)
        # set up initial board:
        draw_grid()
        draw_chips()

        while True:
            # event loop1
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                if event.type == pygame.MOUSEBUTTONDOWN and not game_over:
                    if exit_rectangle.collidepoint(event.pos):
                        sys.exit()
                    elif restart_rectangle.collidepoint(event.pos):
                        main()
                        continue
                    elif reset_rectangle.collidepoint(event.pos):
                        reset = [list(l) for l in reset]
                        original_board = reset
                        draw_chips()
                    else:
                        x, y = event.pos
                        col = int(x // SQUARE_SIZE)
                        row = int(y // SQUARE_SIZE)
                        draw_grid()
                        select(x, y)

                # create the sketch:
                if event.type == pygame.KEYDOWN:
                    if original_board[row][col] == 0:
                        key = keypress()
                        blank(x, y)
                        if board[row][col] != 0:
                            sketch(board[row][col], row, col)

                # finalize the sketch:
                if event.type == pygame.KEYDOWN:
                    if original_board[row][col] == 0:
                        if event.key == pygame.K_KP_ENTER:
                            original_board = [list(l) for l in original_board]
                            original_board[row][col] = board[row][col]
                            blank(x, y)
                            keep(board[row][col], row, col)

            # This part is used to decide the winner and loser
            count = 0
            for item in original_board:
                if 0 in item:
                    count = count + 1
            if count == 0:
                answer = [list(l) for l in answer]
                if original_board == answer:
                    # you would transition into the win screen right now
                    winner = True
                    draw_game_over(screen, winner)
                    print("you win")
                    break
                else:
                    # you would transition into the lose screen right now
                    winner = False
                    draw_game_over(screen, winner)
                    ending = draw_game_over(screen, winner)
                    if ending == 4:
                        main()
                    print("you lose")
                    continue
            pygame.display.update()