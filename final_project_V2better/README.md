# Quick Start Guide - Steganography Tool

This guide will get you up and running with the steganography tool in a few simple steps.

## 1. Building the Tool

First, let's compile the application:

```bash
# Navigate to the source directory
cd /path/to/stego/source

# Build the application
make

# Verify it works
./stego
```

You should see usage information displayed.

## 2. Hiding a Message in an Image

### Prepare Files

1. Find or create a BMP image to use as the carrier (must be 24-bit, uncompressed)
2. Prepare a text file with your secret message

### Encode Command

```bash
./stego encode -i original.bmp -o hidden.bmp -m message.txt -p mysecretpassword
```

This will:
- Take `original.bmp` as the input image
- Create `hidden.bmp` containing your hidden message
- Hide the contents of `message.txt`
- Protect it with the password "mysecretpassword"

You should see a progress bar during the encoding process.

## 3. Extracting a Hidden Message

### Decode Command

```bash
./stego decode -i hidden.bmp -o extracted.txt -p mysecretpassword
```

This will:
- Read `hidden.bmp` which contains the hidden message
- Extract the hidden content to `extracted.txt`
- Use "mysecretpassword" to decrypt the content

## 4. Tips for Best Results

- Use large images for hiding larger messages
- Keep the password safe - without it, you won't be able to recover the message
- BMP files work best when they have complex, colorful content as this helps hide the slight changes

## 5. Common Issues

- If you get "Not a valid BMP file" error, make sure your image is a 24-bit uncompressed BMP file
- If decoding fails with "Invalid steganography signature", check that you're using the correct password and bit position
- If you get "Message too large for the image", either use a larger image or reduce your message size

## 6. Example Scenarios

### Scenario 1: Basic Text Hiding

```bash
# Create a simple text file
echo "This is my secret message" > secret.txt

# Hide it in an image
./stego encode -i photo.bmp -o stego_photo.bmp -m secret.txt

# Later, extract it
./stego decode -i stego_photo.bmp -o recovered.txt
```

### Scenario 2: Protecting with a Password

```bash
# Hide and protect
./stego encode -i photo.bmp -o stego_photo.bmp -m confidential.txt -p "my complex passphrase"

# Later, extract with the same password
./stego decode -i stego_photo.bmp -o recovered.txt -p "my complex passphrase"
```

### Scenario 3: Using a Different Bit Position

```bash
# Hide using bit position 1 instead of the default 0
./stego encode -i photo.bmp -o stego_photo.bmp -m secret.txt -b 1

# Must specify the same bit position when extracting
./stego decode -i stego_photo.bmp -o recovered.txt -b 1
```

Enjoy using the steganography tool for your secret communications!