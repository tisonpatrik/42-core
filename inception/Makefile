COMPOSE   := docker compose -f srcs/docker-compose.yml
ENV_FILE  := srcs/.env
SECRETS   := secrets/db_password.txt secrets/db_root_password.txt secrets/credentials.txt
GEN_PASS  := tr -dc 'A-Za-z0-9' </dev/urandom | head -c 24

# Provides LOGIN, DATA_PATH, ... ; make creates the file first if it is missing.
include $(ENV_FILE)

ifneq ($(wildcard $(ENV_FILE)),)
ifeq ($(strip $(DATA_PATH)),)
$(error DATA_PATH is not set in $(ENV_FILE) (see srcs/.env.example))
endif
endif

DATA_DIRS := $(DATA_PATH)/mariadb $(DATA_PATH)/wordpress

all: up

$(ENV_FILE):
	cp srcs/.env.example $@

secrets/%.txt:
	$(GEN_PASS) > $@

secrets/credentials.txt:
	printf 'WP_ADMIN_PASSWORD=%s\nWP_USER_PASSWORD=%s\n' "$$($(GEN_PASS))" "$$($(GEN_PASS))" > $@

$(DATA_DIRS):
	mkdir -p $@

setup: $(SECRETS) | $(DATA_DIRS)

up: setup
	$(COMPOSE) up -d --build

down:
	$(COMPOSE) down

ps:
	$(COMPOSE) ps

logs:
	$(COMPOSE) logs -f

clean:
	$(COMPOSE) down --rmi all

# Data files are owned by container users, so delete them from inside a container.
fclean:
	$(COMPOSE) down --rmi all --volumes
	docker run --rm -v $(DATA_PATH):/data alpine:3.23 sh -c 'rm -rf /data/*'

re: fclean all

.PHONY: all setup up down ps logs clean fclean re
