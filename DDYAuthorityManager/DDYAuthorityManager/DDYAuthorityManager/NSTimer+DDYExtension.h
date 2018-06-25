#import <Foundation/Foundation.h>

@interface NSTimer (DDYExtension)

+ (NSTimer *)ddy_scheduledTimerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block;

@end
