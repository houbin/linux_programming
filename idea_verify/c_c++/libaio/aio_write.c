#define _GNU_SOURCE		/* syscall() is not POSIX */
 
#include <stdio.h>		/* for perror() */
#include <unistd.h>		/* for syscall() */
#include <sys/syscall.h>	/* for __NR_* definitions */
#include <fcntl.h>		/* O_RDWR */
#include <string.h>		/* memset() */
#include <inttypes.h>	/* uint64_t */
#include <libaio.h>

int main()
{
	io_context_t ctx;
	struct iocb cb;
	struct iocb *cbs = &cb;
	char data[4096];
	struct io_event events[1];
	int ret;
	int write_fd;
    int read_fd;

    memset(data, 'a', 4096);
	write_fd = open("/tmp/testfile", O_WRONLY | O_CREAT);
	if (write_fd < 0) {
		perror("open error");
		return -1;
	}

	ctx = 0;

	ret = io_setup(128, &ctx);
	if (ret < 0) {
		perror("io_setup error");
		return -1;
	}

    io_prep_pwrite(cbs, write_fd, (void *)data, 4096, 0);

	ret = io_submit(ctx, 1, &cbs);
	if (ret != 1) {
  	if (ret < 0)
    		perror("io_submit error");
  	else
  		fprintf(stderr, "could not sumbit IOs");
  	return  -1;
  }

  /* get the reply */
  ret = io_getevents(ctx, 1, 1, events, NULL);
  printf("%d\n", ret);

  struct iocb read_cb;
  struct iocb *read_cbs = &read_cb;

  read_fd = open("/tmp/testfile", O_RDONLY);
  if (read_fd < 0)
  {
    perror("open fd error");
    return -1;
  }

  char read_buffer[123] = {0};
  io_prep_pread(read_cbs, read_fd, read_buffer, 123, 4085);

  ret = io_submit(ctx, 1, &read_cbs);
  if (ret <= 0)
  {
    printf("io_submit return error, ret %d\n", ret);
    return ret;
  }

  struct io_event e;
  struct timespec t;
  t.tv_sec = 4;
  t.tv_nsec = 0;
  ret = io_getevents(ctx, 1, 1, &e, &t);
  if (ret < 0)
  {
    printf("io_getevents return error, ret %d\n", ret);
    return ret;
  }

  printf("read buffer is %s\n", read_buffer);

  ret = io_destroy(ctx);
  if (ret < 0) {
  	perror("io_destroy error");
  	return -1;
  }


  return 0;
}
