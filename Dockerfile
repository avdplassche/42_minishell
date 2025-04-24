FROM alpine:3
RUN apk add --no-cache zsh
RUN apk add --no-cache bash
RUN apk add --no-cache valgrind
RUN apk add --no-cache curl
RUN apk add --no-cache git
RUN apk add --no-cache gcc
RUN apk add --no-cache make
RUN apk add --no-cache gdb
RUN apk add --no-cache mandoc man-pages
RUN apk add --no-cache libx11
RUN apk add --no-cache libxv
RUN apk add --no-cache libx11-dev
RUN apk add --no-cache libc-dev
RUN apk add --no-cache readline-dev
RUN apk add --no-cache libxext-dev
RUN apk add --no-cache libbsd-dev
RUN apk add --no-cache zlib-dev
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
RUN apk add --no-cache py3-pip
RUN python3 -m venv $HOME/.venv && \
		source $HOME/.venv/bin/activate && \
		python3 -m pip install --upgrade pip setuptools && \
		python3 -m pip install norminette && \
		echo "export PATH=$PATH:$HOME/.venv/bin" >> $HOME/.zshrc && \
		deactivate
WORKDIR /app
ENTRYPOINT [ "/bin/zsh" ] 