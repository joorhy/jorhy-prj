.PHONY: clean All

All:
	@echo ----------Building project:[ DahuaHost - Debug ]----------
	@"$(MAKE)" -f "DahuaHost.mk"
clean:
	@echo ----------Cleaning project:[ DahuaHost - Debug ]----------
	@"$(MAKE)" -f "DahuaHost.mk" clean
