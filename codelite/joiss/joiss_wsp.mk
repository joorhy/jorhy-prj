.PHONY: clean All

All:
	@echo ----------Building project:[ JoHost - Debug ]----------
	@"$(MAKE)" -f "JoHost.mk"
clean:
	@echo ----------Cleaning project:[ JoHost - Debug ]----------
	@"$(MAKE)" -f "JoHost.mk" clean
