NAME            := meta-ipsum
WORDBANK        := $(shell ./wordbank $(NAME).c)
WORDBANK_LENGTH := $(shell echo $(WORDBANK) | wc -c | sed 's/^[ \t]*//')
BIN_DIR         := /usr/local/bin

all: build

build: $(NAME).c
	gcc -o $(NAME) $< -D_WORDBANK="\"$(WORDBANK)\"" -D_WORDBANK_LENGTH=$(WORDBANK_LENGTH)

test: build
	@echo "Words:"
	@./$(NAME) -w 3
	@echo ""
	@echo "Sentences:"
	@./$(NAME) -s 3
	@echo ""
	@echo "Paragraphs:"
	@./$(NAME) -p 3

install: $(NAME)
	install -m 0755 $(NAME) $(BIN_DIR)

uninstall:
	rm -f $(BIN_DIR)/$(NAME)

clean:
	rm -f $(NAME)