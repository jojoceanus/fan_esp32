#include <Arduino.h>
#include "motors.h"

// 模拟自然风
unsigned long lastRandomTime = 0;          // 上次生成随机目标值的时间
int autoControl = 0;
int currentDutyCycle = PWM_MIN_DUTY_CYCLE; // 当前占空比
int targetDutyCycle = PWM_MIN_DUTY_CYCLE;  // 目标占空比

// 设置占空比
void setPWM(int dc) {
	// 将百分比转换为LED_CNN的实际值 (0-255)
	int pwmValue = map(dc, 0, 100, 0, 255);
	ledcWrite(0, pwmValue);  // 更新PWM占空比
}

int dutyCycle = 0;

void speedDetectInit() {
	//gpio_set_pull_mode(PAULSE_COUNT_PIN, GPIO_PULLUP_ONLY);  // 启用内部上拉

	// 配置 GPIO 引脚为输入模式并启用内部上拉
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << PAULSE_COUNT_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

	// 配置PCNT脉冲计数器
	pcnt_config_t pcntConfig = {
		.pulse_gpio_num = PAULSE_COUNT_PIN,
		.ctrl_gpio_num = -1,
		.pos_mode = PCNT_COUNT_INC,   // 上升沿计数
		.neg_mode = PCNT_COUNT_DIS,
		.counter_h_lim = PCNT_HIGH_LIMIT,
		.counter_l_lim = PCNT_LOW_LIMIT,
		.unit = PCNT_UNIT,
		.channel = PCNT_CHANNEL
	};
	pcnt_unit_config(&pcntConfig);
	pcnt_counter_pause(PCNT_UNIT);
	pcnt_counter_clear(PCNT_UNIT);
	pcnt_counter_resume(PCNT_UNIT);

	// 脉冲计数滤波器
	pcnt_set_filter_value(PCNT_UNIT, 10);
	pcnt_filter_enable(PCNT_UNIT);

	speedTimerInit();
}

void motorInit() {
	// 配置PWM
	ledcSetup(0, PWM_FREQ, 8);  // 设置通道0，频率和分辨率8
	ledcAttachPin(PWM_PIN, 0);  // 将PWM引脚连接到通道0

	// 默认反转
	pinMode(CCW_PIN, OUTPUT);
	digitalWrite(CCW_PIN, LOW);

	speedDetectInit();

	// 设置默认占空比
	setPWM(50);
	dutyCycle = 50;
}

void simulateNaturalWind() {
	unsigned long currentTime = millis();

	// 每隔 RANDOM_INTERVAL 毫秒生成一个新的随机目标占空比
	if (currentTime - lastRandomTime >= RANDOM_INTERVAL) {
		targetDutyCycle = random(PWM_MIN_DUTY_CYCLE, PWM_MAX_DUTY_CYCLE + 1); // 随机生成目标值
		lastRandomTime = currentTime;
	}

	// 平滑过渡到目标占空比
	if (currentDutyCycle < targetDutyCycle) {
		currentDutyCycle += FADE_STEP; // 增加占空比
		if (currentDutyCycle > targetDutyCycle) {
		currentDutyCycle = targetDutyCycle; // 防止超过目标值
		}
	} else if (currentDutyCycle > targetDutyCycle) {
		currentDutyCycle -= FADE_STEP; // 减少占空比
		if (currentDutyCycle < targetDutyCycle) {
		currentDutyCycle = targetDutyCycle; // 防止低于目标值
		}
	}
	// 更新PWM占空比
	setPWM(currentDutyCycle);
}