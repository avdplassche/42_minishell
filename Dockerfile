FROM alpine:3
RUN apk add --no-cache zsh
RUN apk add --no-cache bash
RUN apk add --no-cache valgrind
RUN apk add --no-cache curl
RUN apk add --no-cache git
RUN apk add --no-cache gcc
RUN apk add --no-cache make
RUN apk add --no-cache libc-dev
RUN apk add --no-cache readline-dev
RUN apk add linux-headers
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
ENTRYPOINT [ "/bin/zsh" ]