FROM		ubuntu:latest

RUN			apt update && apt install -y clang make git

WORKDIR		/.github/checker

ENTRYPOINT	[ "make", "check" ]
