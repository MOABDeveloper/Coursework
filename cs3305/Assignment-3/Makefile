assignment-3: assignment-3.c
	gcc -o assignment-3 assignment-3.c -pthread

clean:
	rm -f assignment-3

run-all-valid: assignment-3
	@for file in valid*.txt; do \
		echo "Running $$file..."; \
		./assignment-3 $$file; \
	done

run-all-invalid: assignment-3
	@for file in invalid*.txt; do \
		 echo "Running $$file..."; \
		./assignment-3 $$file; \
	done
