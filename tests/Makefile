.PHONY: all
all: minishell build test

.PHONY: build
build:
	docker build -t fuzzer .

.PHONY: fuzz
fuzz: minishell build
	@echo 'Doing 10K random fuzz tests inside a container, this will take some time...'
	docker run --rm fuzzer 2> fuzzing.txt

.PHONY: clean
clean:
	docker image prune

minishell:
	make -C ..
	cp ../$@ .

.PHONY: test
test: minishell
	./msh_tests.sh
