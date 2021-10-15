def validPadding(bytes):
    padding = bytes[len(bytes) - 1]
    for byte in bytes[len(bytes)-padding:]:
        if byte != padding:
            return False
    return True