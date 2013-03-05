.PHONY: clean All

All:
	@echo ----------Building project:[ MCControl - Debug ]----------
	@"$(MAKE)" -f "MCControl.mk"
clean:
	@echo ----------Cleaning project:[ MCControl - Debug ]----------
	@"$(MAKE)" -f "MCControl.mk" clean
