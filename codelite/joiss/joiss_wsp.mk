.PHONY: clean All

All:
	@echo ----------Building project:[ AipstarHost - Debug ]----------
	@"$(MAKE)" -f "AipstarHost.mk"
clean:
	@echo ----------Cleaning project:[ AipstarHost - Debug ]----------
	@"$(MAKE)" -f "AipstarHost.mk" clean
