FROM ubuntu:18.04

COPY minishell .
COPY fuzzing.sh .

ENTRYPOINT ["/bin/bash", "-c", "bash ./fuzzing.sh 1>&2"]
