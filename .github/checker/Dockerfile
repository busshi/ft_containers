FROM		ubuntu:latest

RUN			apt update && apt install -y clang make git valgrind

WORKDIR		/.github/checker

ENTRYPOINT	[ "make", "check" ]
