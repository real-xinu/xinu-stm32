# Use Alpine Linux as base image
FROM alpine

# update and install cross compiler
RUN apk update && \
    apk add --no-cache gcc-arm-none-eabi 

# required build tools
RUN apk add flex flex-dev bison gawk make libc-dev

# Set working directory
WORKDIR /app

# Define the entry point for your container
CMD ["sh"]
