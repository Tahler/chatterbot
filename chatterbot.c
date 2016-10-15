#include <stdio.h>
#include <stdbool.h>

const char MESSAGE_TERMINATOR = '\n';
const char* PROMPT = "> ";

enum State {
  START,

  H,
  HE,
  HEL,
  HELL,
  HELLO,
  HO,
  HOW,
  HOWD,
  HOWDY,
  HOW_,
  HOW_D,
  HOW_DO,
  HOW_DO_,
  HOW_DO_Y,
  HOW_DO_YO,
  HOW_DO_YOU,
  HOW_DO_YOU_,
  HOW_DO_YOU_D,
  HOW_DO_YOU_DO,
  HOW_DO_YOU_DOQ,
  HO_,
  HO_H,
  HO_HO,
  E,
  EX,
  EXI,
  EXIT,

  FAIL
};

enum State transition(enum State current_state, char next_char) {
  enum State next_state;
  switch (current_state) {
      case START:
        switch (next_char) {
          case 'h':
            next_state = H;
            break;
          case 'e':
            next_state = E;
            break;
        }
        break;

      case H:
        switch (next_char) {
          case 'e':
            next_state = HE;
            break;
          case 'o':
            next_state = HO;
            break;
        }
        break;
      case HE:
        switch (next_char) {
          case 'l':
            next_state = HEL;
            break;
        }
        break;
      case HEL:
        switch (next_char) {
          case 'l':
            next_state = HELL;
            break;
        }
        break;
      case HELL:
        switch (next_char) {
          case 'o':
            next_state = HELLO;
            break;
        }
        break;
      case HELLO:
        next_state = FAIL;
        break;
      case HO:
        switch (next_char) {
          case 'w':
            next_state = HOW;
            break;
          case ' ':
            next_state = HO_;
            break;
        }
        break;
      case HOW:
        switch (next_char) {
          case 'd':
            next_state = HOWD;
            break;
          case ' ':
            next_state = HOW_;
            break;
        }
        break;
      case HOWD:
        switch (next_char) {
          case 'y':
            next_state = HOWDY;
            break;
        }
        break;
      case HOWDY:
        next_state = FAIL;
        break;
      case HOW_:
        switch (next_char) {
          case 'd':
            next_state = HOW_D;
            break;
        }
        break;
      case HOW_D:
        switch (next_char) {
          case 'o':
            next_state = HOW_DO;
            break;
        }
        break;
      case HOW_DO:
        switch (next_char) {
          case ' ':
            next_state = HOW_DO_;
            break;
        }
        break;
      case HOW_DO_:
        switch (next_char) {
          case 'y':
            next_state = HOW_DO_Y;
            break;
        }
        break;
      case HOW_DO_Y:
        switch (next_char) {
          case 'o':
            next_state = HOW_DO_YO;
            break;
        }
        break;
      case HOW_DO_YO:
        switch (next_char) {
          case 'u':
            next_state = HOW_DO_YOU;
            break;
        }
        break;
      case HOW_DO_YOU:
        switch (next_char) {
          case ' ':
            next_state = HOW_DO_YOU_;
            break;
        }
        break;
      case HOW_DO_YOU_:
        switch (next_char) {
          case 'd':
            next_state = HOW_DO_YOU_D;
            break;
        }
        break;
      case HOW_DO_YOU_D:
        switch (next_char) {
          case 'o':
            next_state = HOW_DO_YOU_DO;
            break;
        }
        break;
      case HOW_DO_YOU_DO:
        switch (next_char) {
          case '?':
            next_state = HOW_DO_YOU_DOQ;
            break;
        }
        break;
      case HOW_DO_YOU_DOQ:
        next_state = FAIL;
        break;
      case HO_:
        switch (next_char) {
          case 'h':
            next_state = HO_H;
            break;
        }
        break;
      case HO_H:
        switch (next_char) {
          case 'o':
            next_state = HO_HO;
            break;
        }
        break;
      case HO_HO:
        switch (next_char) {
          case ' ':
            next_state = HO_;
            break;
          default:
            printf("FAIL");
            next_state = FAIL;
            break;
        }
        break;
      case E:
        switch (next_char) {
          case 'x':
            next_state = EX;
            break;
        }
        break;
      case EX:
        switch (next_char) {
          case 'i':
            next_state = EXI;
            break;
        }
        break;
      case EXI:
        switch (next_char) {
          case 't':
            next_state = EXIT;
            break;
        }
        break;
      case EXIT:
        next_state = FAIL;
        break;
      case FAIL:
        // Do nothing
        break;
    }
    return next_state;
}

void prompt() {
  printf("%s", PROMPT);
}

enum State read_input() {
  prompt();

  enum State current_state = START;
  bool more_input = true;
  while (more_input) {
    char next_char = getchar();
    if (next_char == MESSAGE_TERMINATOR) {
      more_input = false;
    } else {
      current_state = transition(current_state, next_char);
    }
  }
  return current_state;
}

char* response_for_state(enum State state) {
  char* response;
  switch (state) {
    case HELLO:
      response = "Hi";
      break;
    case HOWDY:
      response = "Let's Ride!";
      break;
    case HOW_DO_YOU_DOQ:
      response = "I do fine, and you?";
      break;
    case HO_HO:
      response = "You must be quite the jolly person";
      break;
    case EXIT:
      response = "Bye!";
      break;
    default:
      response = "Tell me about yourself";
      break;
  }
  return response;
}

void respond(char* message) {
  printf("%s%c", message, MESSAGE_TERMINATOR);
}

int main()
{
  bool conversing = true;
  while (conversing) {
    enum State final_state = read_input();

    char* response = response_for_state(final_state);
    respond(response);

    conversing = final_state != EXIT;
  }
}
