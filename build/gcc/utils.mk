$(UTILS_BIN_DIR)/$(UTILS_1): $(UTILS_SRC_DIR)/schemaHandling/createGrammars.c $(BIN_DIR)/libexip.a
		$(CC) $(CFLAGS) $(UTILS_SRC_DIR)/schemaHandling/createGrammars.c $(BIN_DIR)/libexip.a -o $(UTILS_BIN_DIR)/$(UTILS_1)