def __init__(self):
    super().__init__('lidar_front_filter')
    
    # پارامترهای قابل تنظیم
    self.declare_parameter('front_angle_range', 90.0)  # محدوده زاویه جلویی
    self.declare_parameter('min_range', 0.1)         # حداقل فاصله (متر)
    self.declare_parameter('max_range', 12.0)        # حداکثر فاصله (متر)
    self.declare_parameter('input_topic', '/scan_ktz')
    self.declare_parameter('output_topic', '/scan')
    
    # دریافت پارامترها
    self.min_range = self.get_parameter('min_range').value
    self.max_range = self.get_parameter('max_range').value
    # ... بقیه پارامترها